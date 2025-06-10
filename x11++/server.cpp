#include <X11/X.h>
#include <X11/Xlib.h>
#include <x11++/eventType.hpp> // Asegúrate de que esta ruta es correcta
#include <x11++/server.hpp>
#include <mask.hpp> // Asegúrate de que esta ruta es correcta
#include <iostream> // Para mensajes de error/depuración
#include <X11/Xutil.h>
#include <X11/keysym.h>

namespace x {

// Constructor y destructor
Server::Server(const char* _displayname) : displayname(_displayname) {}

Server::~Server(){
    ungrabAnyKey();
    ungrabAnyButton();
    disconnect();
}

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

void Server::quit(){
    stop = true;
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
    }
}

void Server::ungrabAnyKey(){
    if (display != nullptr) {
        XUngrabKey(display, AnyKey, AnyModifier, DefaultRootWindow(display));
        XFlush(display);
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
    }
}

void Server::ungrabAnyButton(){
    if (display != nullptr) {
        XUngrabButton(display, AnyButton, AnyModifier, DefaultRootWindow(display));
        XFlush(display);
    }
}

void Server::listen(){
    bool needs_key_grab = eventMask.contains(KeyPressMask) || eventMask.contains(KeyReleaseMask);
    bool needs_button_grab = eventMask.contains(ButtonPressMask) || eventMask.contains(ButtonReleaseMask) || eventMask.contains(PointerMotionMask);

    grabAnyKey(needs_key_grab); // Teclado en modo Sync
    grabAnyButton(needs_button_grab); // Ratón en modo Sync
    XSelectInput(display, DefaultRootWindow(display), eventMask.unwrap());
    XFlush(display); // Asegura que todos los comandos se envían al servidor

    for(;;){ // Bucle infinito para escuchar eventos
        nextEvent(); // Rellena 'this->event'
        switch (EventType(event.type)) {
            case EventType::keyPress:
            {
                for (auto& listener : listeners_keyPress) listener(&event);
                XAllowEvents(display, ReplayKeyboard, cast<XKeyEvent*>(&event)->time);
                XFlush(display); // Asegura que la instrucción XAllowEvents se envía
            }
            break;

            case EventType::keyRelease:
            {
                for (auto& listener : listeners_keyRelease) listener(&event);
                XAllowEvents(display, ReplayKeyboard, cast<XKeyEvent*>(&event)->time);
                XFlush(display);
            }
            break;

            case EventType::buttonPress:
            {
                for (auto& listener : listeners_buttonPress) listener(&event);
                XAllowEvents(display, ReplayPointer, cast<XButtonEvent*>(&event)->time); // ReplayPointer para eventos de ratón
                XFlush(display);
            }
            break;

            case EventType::buttonRelease:
            {
                for (auto& listener : listeners_buttonRelease) listener(&event);
                XAllowEvents(display, ReplayPointer, cast<XButtonEvent*>(&event)->time);
                XFlush(display);
            }
            break;

            case EventType::motionNotify:
            {
                for (auto& listener : listeners_motionNotify) listener(&event);
                XAllowEvents(display, ReplayPointer, cast<XMotionEvent*>(&event)->time);
                XFlush(display);
            }
            break;

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
        }
        if(stop) break;
    }
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