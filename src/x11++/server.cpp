#include <X11/X.h>
#include <X11/Xlib.h>
#include <x11++/eventType.hpp> // Asegúrate de que esta ruta es correcta
#include <x11++/server.hpp>
#include <mask.hpp> // Asegúrate de que esta ruta es correcta
#include <iostream> // Para mensajes de error/depuración

// Necesitas X11/Xutil.h para XKeysymToKeycode, aunque no lo usemos directamente aquí
// y X11/keysym.h para AnyKey, AnyModifier, etc.
#include <X11/Xutil.h>
#include <X11/keysym.h>

namespace x {

// Constructor y destructor
Server::Server(const char* _displayname) : displayname(_displayname) {
    // Inicializar eventMask aquí si tu clase Mask lo requiere
    // eventMask = Mask(); // Si Mask tiene un constructor por defecto
}

Server::~Server(){
    // Asegúrate de liberar los grabs antes de desconectar el display
    ungrabAnyKey();
    ungrabAnyButton();
    disconnect();
}

// ... (Tus métodos connect, disconnect, raiseWindow, moveAndResizeWindow, etc.) ...

bool Server::connect(){
    display = XOpenDisplay(displayname);
    if (display == nullptr) {
        std::cerr << "Error: No se pudo conectar al servidor X. Asegúrate de que el servidor X está corriendo y la variable DISPLAY está configurada." << std::endl;
        return false;
    }
    return true;
}

void Server::disconnect(){
    if(display != nullptr) {
        XCloseDisplay(display);
        display = nullptr; // Buenas prácticas: establece el puntero a nullptr después de liberarlo
    }
}

// ... (Tus métodos existentes de manipulación de ventanas) ...

_XEvent* Server::getEvent(){
    return &event;
}

void Server::nextEvent(){
    XNextEvent(display,&event);
}

void Server::addRootSelectInput(long _eventMask){
    if (eventMask.contains(_eventMask)) return;
    eventMask.add(_eventMask);
}

// --- MÉTODOS GRAB MODIFICADOS ---
void Server::grabAnyKey(bool condition){
    if (condition && display != nullptr){
        int result = XGrabKey(
            display, 
            AnyKey, 
            AnyModifier, 
            DefaultRootWindow(display),
            False, 
            GrabModeAsync, 
            GrabModeSync
        ); // owner_events = False
        XFlush(display);
        if (result == GrabSuccess) {
            std::cout << "XGrabKey(AnyKey, AnyModifier) exitoso. Modos: P=" << GrabModeAsync << ", K=" << GrabModeSync << std::endl;
        } else {
            std::cerr << "XGrabKey(AnyKey, AnyModifier) FALLÓ. Código: " << result << std::endl;
        }
    }
}

void Server::ungrabAnyKey(){
    if (display != nullptr) {
        XUngrabKey(display, AnyKey, AnyModifier, DefaultRootWindow(display));
        XFlush(display);
        std::cout << "XUngrabKey(AnyKey, AnyModifier) llamado." << std::endl;
    }
}

void Server::grabAnyButton(bool condition){
    if (condition && display != nullptr){
        int result = XGrabButton(
            display, 
            AnyButton, 
            AnyModifier, 
            DefaultRootWindow(display),
            False, 
            ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
            GrabModeSync, 
            GrabModeAsync, 
            None, 
            None
        ); // owner_events = False
        XFlush(display);
        if (result == GrabSuccess) {
            std::cout   << "XGrabButton(AnyButton, AnyModifier) exitoso. Máscara eventos: " << (ButtonPressMask | ButtonReleaseMask | PointerMotionMask)
                        << ", Modos: P=" << GrabModeSync << ", K=" << GrabModeAsync << std::endl;
        } else {
            std::cerr << "XGrabButton(AnyButton, AnyModifier) FALLÓ. Código: " << result << std::endl;
        }
    }
}

void Server::ungrabAnyButton(){
    if (display != nullptr) {
        XUngrabButton(display, AnyButton, AnyModifier, DefaultRootWindow(display));
        XFlush(display);
        std::cout << "XUngrabButton(AnyButton, AnyModifier) llamado." << std::endl;
    }
}

// --- BUCLE DE EVENTOS MODIFICADO ---
void Server::listen(){
    // Determina si se necesitan grabs de teclado o ratón
    bool needs_key_grab = eventMask.contains(KeyPressMask) || eventMask.contains(KeyReleaseMask);
    bool needs_button_grab = eventMask.contains(ButtonPressMask) || eventMask.contains(ButtonReleaseMask) || eventMask.contains(PointerMotionMask);

    // Intenta realizar los grabs.
    // Usamos GrabModeSync para el teclado y el ratón para poder controlar
    // el flujo de eventos y "dejarles pasar" con XAllowEvents.
    // GrabModeAsync para el otro dispositivo para no bloquearlo.
    if (needs_key_grab) {
        grabAnyKey(true); // Teclado en modo Sync
    }
    if (needs_button_grab) {
        // Necesitas especificar la máscara de eventos para XGrabButton
        // Es la máscara de eventos que recibirás mientras el grab esté activo.
        grabAnyButton(true); // Ratón en modo Sync
    }

    // XSelectInput sigue siendo necesario para eventos que NO son grabs,
    // o para eventos que ocurren directamente en la ventana raíz y no son cubiertos por un grab.
    XSelectInput(display, DefaultRootWindow(display), eventMask.unwrap());
    XFlush(display); // Asegura que todos los comandos se envían al servidor

    std::cout << "Iniciando bucle de escucha de eventos..." << std::endl;

    for(;;){ // Bucle infinito para escuchar eventos
        nextEvent(); // Rellena 'this->event'

        // NOTA: Es crucial que el cast a la estructura de evento específica
        // se haga *dentro* del case, después de verificar el tipo de evento.
        // Y XAllowEvents solo debe llamarse para eventos que fueron grabados en modo Sync.

        switch (EventType(event.type)) {
            case EventType::keyPress:
            {
                XKeyEvent* key_event = reinterpret_cast<XKeyEvent*>(&event);
                for (auto& listener : listeners_keyPress) {
                    listener(&event);
                }
                // Si el teclado fue grabado en Sync mode, debemos permitir que el evento continúe
                // Usamos ReplayKeyboard para que el evento se reenvíe a la aplicación con foco
                XAllowEvents(display, ReplayKeyboard, key_event->time);
                XFlush(display); // Asegura que la instrucción XAllowEvents se envía
            }
            break;

            case EventType::keyRelease:
            {
                XKeyEvent* key_event = reinterpret_cast<XKeyEvent*>(&event);
                for (auto& listener : listeners_keyRelease) {
                    listener(&event);
                }
                XAllowEvents(display, ReplayKeyboard, key_event->time);
                XFlush(display);
            }
            break;

            case EventType::buttonPress:
            {
                XButtonEvent* button_event = reinterpret_cast<XButtonEvent*>(&event);
                for (auto& listener : listeners_buttonPress) {
                    listener(&event);
                }
                // Si el puntero fue grabado en Sync mode, debemos permitir que el evento continúe
                XAllowEvents(display, ReplayPointer, button_event->time); // ReplayPointer para eventos de ratón
                XFlush(display);
            }
            break;

            case EventType::buttonRelease:
            {
                XButtonEvent* button_event = reinterpret_cast<XButtonEvent*>(&event);
                for (auto& listener : listeners_buttonRelease) {
                    listener(&event);
                }
                XAllowEvents(display, ReplayPointer, button_event->time);
                XFlush(display);
            }
            break;

            case EventType::motionNotify:
            {
                XMotionEvent* motion_event = reinterpret_cast<XMotionEvent*>(&event);
                for (auto& listener : listeners_motionNotify) {
                    listener(&event);
                }
                XAllowEvents(display, ReplayPointer, motion_event->time);
                XFlush(display);
            }
            break;
            // ... (Resto de tus cases para otros tipos de eventos, sin XAllowEvents incondicional) ...

            // Aquí van el resto de tus 'case' de EventType.
            // Para eventos que NO fueron grabados en modo Sync (como ConfigureRequest, Expose, etc.),
            // NO debes llamar a XAllowEvents. Esos eventos ya fluyen normalmente.
            // Solo los KeyPress/KeyRelease y ButtonPress/ButtonRelease/MotionNotify
            // que están siendo interceptados por un grab Sync necesitan XAllowEvents.

            case EventType::enterNotify:
                for (auto& listener : listeners_enterNotify) { listener(getEvent()); }
                break;
            case EventType::leaveNotify:
                for (auto& listener : listeners_leaveNotify) { listener(getEvent()); }
                break;
            case EventType::focusIn:
                for (auto& listener : listeners_focusIn) { listener(getEvent()); }
                break;
            case EventType::focusOut:
                for (auto& listener : listeners_focusOut) { listener(getEvent()); }
                break;
            case EventType::keymapNotify:
                for (auto& listener : listeners_keymapNotify) { listener(getEvent()); }
                break;
            case EventType::expose:
                for (auto& listener : listeners_expose) { listener(getEvent()); }
                break;
            case EventType::graphicsExpose:
                for (auto& listener : listeners_graphicsExpose) { listener(getEvent()); }
                break;
            case EventType::noExpose:
                for (auto& listener : listeners_noExpose) { listener(getEvent()); }
                break;
            case EventType::circulateRequest:
                for (auto& listener : listeners_circulateRequest) { listener(getEvent()); }
                break;
            case EventType::configureRequest:
                for (auto& listener : listeners_configureRequest) { listener(getEvent()); }
                break;
            case EventType::mapRequest:
                for (auto& listener : listeners_mapRequest) { listener(getEvent()); }
                break;
            case EventType::resizeRequest:
                for (auto& listener : listeners_resizeRequest) { listener(getEvent()); }
                break;
            case EventType::circulateNotify:
                for (auto& listener : listeners_circulateNotify) { listener(getEvent()); }
                break;
            case EventType::configureNotify:
                for (auto& listener : listeners_configureNotify) { listener(getEvent()); }
                break;
            case EventType::createNotify:
                for (auto& listener : listeners_createNotify) { listener(getEvent()); }
                break;
            case EventType::destroyNotify:
                for (auto& listener : listeners_destroyNotify) { listener(getEvent()); }
                break;
            case EventType::gravityNotify:
                for (auto& listener : listeners_gravityNotify) { listener(getEvent()); }
                break;
            case EventType::mapNotify:
                for (auto& listener : listeners_mapNotify) { listener(getEvent()); }
                break;
            case EventType::mappingNotify:
                for (auto& listener : listeners_mappingNotify) { listener(getEvent()); }
                break;
            case EventType::reparentNotify:
                for (auto& listener : listeners_reparentNotify) { listener(getEvent()); }
                break;
            case EventType::unmapNotify:
                for (auto& listener : listeners_unmapNotify) { listener(getEvent()); }
                break;
            case EventType::visibilityNotify:
                for (auto& listener : listeners_visibilityNotify) { listener(getEvent()); }
                break;
            case EventType::colormapNotify:
                for (auto& listener : listeners_colormapNotify) { listener(getEvent()); }
                break;
            case EventType::clientMessage:
                for (auto& listener : listeners_clientMessage) { listener(getEvent()); }
                break;
            case EventType::propertyNotify:
                for (auto& listener : listeners_propertyNotify) { listener(getEvent()); }
                break;
            case EventType::selectionClear:
                for (auto& listener : listeners_selectionClear) { listener(getEvent()); }
                break;
            case EventType::selectionNotify:
                for (auto& listener : listeners_selectionNotify) { listener(getEvent()); }
                break;
            case EventType::selectionRequest:
                for (auto& listener : listeners_selectionRequest) { listener(getEvent()); }
                break;

            default:
                // Puedes imprimir eventos no manejados para depuración
                // std::cout << "Evento no manejado: " << event.type << std::endl;
                break;
        }
    }
    // Estas líneas no se ejecutarán porque el bucle for(;;) es infinito.
    // La liberación de grabs debe manejarse en el destructor o con un mecanismo de salida.
    // XUngrabButton(display, AnyKey, AnyModifier, DefaultRootWindow(display)); // Esto estaba mal, era XUngrabKey
    // XUngrabKey(display, AnyKey, AnyModifier, DefaultRootWindow(display));
    // XFlush(display);
}

void Server::addRootEventListener(EventType type,EventCallback listener){
    switch (type) {
        case EventType::keyPress:
            listeners_keyPress.push_back(listener);
            addRootSelectInput(KeyPressMask);
            break;
        case EventType::keyRelease:
            listeners_keyRelease.push_back(listener);
            addRootSelectInput(KeyReleaseMask);
            break;
        case EventType::buttonPress:
            listeners_buttonPress.push_back(listener);
            addRootSelectInput(ButtonPressMask);
            break;
        case EventType::buttonRelease:
            listeners_buttonRelease.push_back(listener);
            addRootSelectInput(ButtonReleaseMask);
            break;
        case EventType::motionNotify:
            listeners_motionNotify.push_back(listener);
            // MotionNotifyMask es la máscara correcta, no MotionNotify (que es el tipo de evento)
            addRootSelectInput(PointerMotionMask);
            break;
        case EventType::enterNotify:
            listeners_enterNotify.push_back(listener);
            addRootSelectInput(EnterWindowMask); // Correcto es EnterWindowMask
            break;
        case EventType::leaveNotify:
            listeners_leaveNotify.push_back(listener);
            addRootSelectInput(LeaveWindowMask); // Correcto es LeaveWindowMask
            break;
        case EventType::focusIn:
            listeners_focusIn.push_back(listener);
            addRootSelectInput(FocusChangeMask); // Se usa FocusChangeMask para FocusIn/Out
            break;
        case EventType::focusOut:
            listeners_focusOut.push_back(listener);
            addRootSelectInput(FocusChangeMask); // Se usa FocusChangeMask para FocusIn/Out
            break;
        case EventType::keymapNotify:
            listeners_keymapNotify.push_back(listener);
            addRootSelectInput(KeymapStateMask); // Correcto es KeymapStateMask
            break;
        case EventType::expose:
            listeners_expose.push_back(listener);
            addRootSelectInput(ExposureMask); // Correcto es ExposureMask
            break;
        case EventType::graphicsExpose:
            // GraphicsExpose y NoExpose son eventos de Extensiones (render, shape, etc.)
            // y no tienen máscaras XSelectInput estándar.
            // Usualmente se seleccionan a través de la extensión XRender, no con XSelectInput.
            // Si no estás usando una extensión X que los genere, nunca los recibirás vía XSelectInput.
            // Para este ejemplo, podemos dejarlo sin addRootSelectInput o añadir un comentario.
            listeners_graphicsExpose.push_back(listener);
            // addRootSelectInput(GraphicsExposeMask); // No existe directamente
            break;
        case EventType::noExpose:
            listeners_noExpose.push_back(listener);
            // addRootSelectInput(NoExposeMask); // No existe directamente
            break;
        case EventType::circulateRequest:
            listeners_circulateRequest.push_back(listener);
            addRootSelectInput(SubstructureRedirectMask); // Para CirculateRequest, ConfigureRequest, MapRequest
            break;
        case EventType::configureRequest:
            listeners_configureRequest.push_back(listener);
            addRootSelectInput(SubstructureRedirectMask);
            break;
        case EventType::mapRequest:
            listeners_mapRequest.push_back(listener);
            addRootSelectInput(SubstructureRedirectMask);
            break;
        case EventType::resizeRequest:
            listeners_resizeRequest.push_back(listener);
            addRootSelectInput(ResizeRedirectMask); // Correcto es ResizeRedirectMask
            break;
        case EventType::circulateNotify:
            listeners_circulateNotify.push_back(listener);
            addRootSelectInput(SubstructureNotifyMask); // Para Notify eventos de subestructura
            break;
        case EventType::configureNotify:
            listeners_configureNotify.push_back(listener);
            addRootSelectInput(StructureNotifyMask); // Para ConfigureNotify de la propia ventana
            addRootSelectInput(SubstructureNotifyMask); // Para ConfigureNotify de hijos
            break;
        case EventType::createNotify:
            listeners_createNotify.push_back(listener);
            addRootSelectInput(SubstructureNotifyMask);
            break;
        case EventType::destroyNotify:
            listeners_destroyNotify.push_back(listener);
            addRootSelectInput(SubstructureNotifyMask);
            break;
        case EventType::gravityNotify:
            listeners_gravityNotify.push_back(listener);
            addRootSelectInput(StructureNotifyMask);
            break;
        case EventType::mapNotify:
            listeners_mapNotify.push_back(listener);
            addRootSelectInput(SubstructureNotifyMask);
            break;
        case EventType::mappingNotify:
            listeners_mappingNotify.push_back(listener);
            addRootSelectInput(MappingNotify); // MappingNotify no tiene una máscara XSelectInput, se recibe siempre si se usa XKeyboardControl
            break;
        case EventType::reparentNotify:
            listeners_reparentNotify.push_back(listener);
            addRootSelectInput(SubstructureNotifyMask);
            break;
        case EventType::unmapNotify:
            listeners_unmapNotify.push_back(listener);
            addRootSelectInput(SubstructureNotifyMask);
            break;
        case EventType::visibilityNotify:
            listeners_visibilityNotify.push_back(listener);
            addRootSelectInput(VisibilityChangeMask); // Correcto es VisibilityChangeMask
            break;
        case EventType::colormapNotify:
            listeners_colormapNotify.push_back(listener);
            addRootSelectInput(ColormapChangeMask); // Correcto es ColormapChangeMask
            break;
        case EventType::clientMessage:
            listeners_clientMessage.push_back(listener);
            // ClientMessage no tiene una máscara XSelectInput, se envían con XSendEvent
            break;
        case EventType::propertyNotify:
            listeners_propertyNotify.push_back(listener);
            addRootSelectInput(PropertyChangeMask); // Correcto es PropertyChangeMask
            break;
        case EventType::selectionClear:
            listeners_selectionClear.push_back(listener);
            // Las selecciones no se seleccionan con XSelectInput
            break;
        case EventType::selectionNotify:
            listeners_selectionNotify.push_back(listener);
            // Las selecciones no se seleccionan con XSelectInput
            break;
        case EventType::selectionRequest:
            listeners_selectionRequest.push_back(listener);
            // Las selecciones no se seleccionan con XSelectInput
            break;

        default:
            break;
    }
}

} // namespace x