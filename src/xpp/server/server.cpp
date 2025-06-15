#include "server.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <xpp/event/eventType.hpp> // Asegúrate de que esta ruta es correcta
#include <xpp/mask/mask.hpp> // Asegúrate de que esta ruta es correcta
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

void Server::quitLoop(){
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

void Server::keyMap(long modifier, std::string key, EventCallback listener){}

void Server::listen(){
    bool needs_key_grab = eventMask.contains(KeyPressMask) || eventMask.contains(KeyReleaseMask);
    bool needs_button_grab = eventMask.contains(ButtonPressMask) || eventMask.contains(ButtonReleaseMask) || eventMask.contains(PointerMotionMask);

    grabAnyKey(needs_key_grab); // Teclado en modo Sync
    grabAnyButton(needs_button_grab); // Ratón en modo Sync
    XSelectInput(display, DefaultRootWindow(display), eventMask.unwrap());
    XFlush(display); // Asegura que todos los comandos se envían al servidor

    while(stop){ // Bucle infinito para escuchar eventos
        nextEvent(); // Rellena 'this->event'
        for (auto& listener : eventListeners[EventType(event.type)]) listener(&event);
        XAllowEvents(display, ReplayKeyboard, cast<XKeyEvent*>(&event)->time);
        XFlush(display); // Asegura que la instrucción XAllowEvents se envía
    }
}

void Server::updateEventMaskForRoot(EventType type) {
    // Determina la máscara de X11 correspondiente y añádela a eventMask
    long x_event_mask = 0;
    switch (type) {
        case EventType::keyPress:
            x_event_mask = KeyPressMask;
            break;
        case EventType::keyRelease:
            x_event_mask = KeyReleaseMask;
            break;
        case EventType::buttonPress:
            x_event_mask = ButtonPressMask;
            break;
        case EventType::buttonRelease:
            x_event_mask = ButtonReleaseMask;
            break;
        case EventType::motionNotify: // Movimiento del puntero
            x_event_mask = PointerMotionMask;
            break;
        case EventType::enterNotify: // Puntero entra a la ventana
            x_event_mask = EnterWindowMask;
            break;
        case EventType::leaveNotify: // Puntero sale de la ventana
            x_event_mask = LeaveWindowMask;
            break;
        case EventType::focusIn:
        case EventType::focusOut:
            x_event_mask = FocusChangeMask;
            break;
        case EventType::expose:
            x_event_mask = ExposureMask;
            break;
        default:
            break;
    }

    if (x_event_mask != 0) {
        addRootSelectInput(x_event_mask); // Llama al método privado para añadir la máscara
    }
}

void Server::addRootEventListener(EventType type,EventCallback listener){
    // Almacena el callback para el tipo de evento
    eventListeners[type].push_back(listener);
    // Actualiza la máscara de eventos para la ventana raíz
    updateEventMaskForRoot(type);
}

} // namespace x