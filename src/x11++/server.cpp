#include "X11/X.h"
#include "X11/Xlib.h"
#include "x11++/eventType.hpp"
#include <x11++/server.hpp>

    using namespace x;

    Server::Server(const char* _displayname) : displayname(_displayname) {}
    Server::~Server(){ disconnect(); }

    bool Server::connect(){
        display = XOpenDisplay(displayname);
        return display != nullptr;
    }

    void Server::disconnect(){
        if(display != nullptr) XCloseDisplay(display);
    }

    void Server::raiseWindow(Window window){
        XRaiseWindow(display, window);  
    }

    void Server::moveAndResizeWindow(Window window, int initx, int inity, unsigned int width, unsigned int height){
        XMoveResizeWindow(display, window, initx, inity, width, height);
        XFlush(display);
    }

    void Server::moveWindow(Window window, int initx, int inity){
        XMoveWindow(display, window, initx, inity);
        XFlush(display);
    }

    void Server::resizeWindow(Window window, unsigned int width, unsigned int height){
        XResizeWindow(display, window, width, height);
        XFlush(display);
    }

    XWindowAttributes Server::getWindowAttributes(Window window){
        XWindowAttributes attrs;
        XGetWindowAttributes(display, window, &attrs);
        return attrs;
    }

    void Server::fillWindowAttributes(Window window, XWindowAttributes* attrs){
        XGetWindowAttributes(display, window, attrs);
    }

    void Server::nextEvent(){
        XNextEvent(display,&event);
    }

    void Server::addRootSelectInput(long _eventMask){
        if(eventMask == 0) eventMask = _eventMask;
        else if ((eventMask & _eventMask) == _eventMask) return; 
        else eventMask |= _eventMask;
    }

    Event* Server::getEvent(){
        return &event;
    }

    void Server::listen(){
        XSelectInput(display, DefaultRootWindow(display), eventMask);
        for(;;){
            nextEvent();
            switch (EventType(event.type)) {
                case EventType::keyPress:
                    for (auto& listener : listeners_keyPress) {
                        listener(getEvent()); // Pass the event data to the listener
                    }
                    break;

                case EventType::keyRelease:
                    for (auto& listener : listeners_keyRelease) {
                        listener(getEvent());
                    }
                    break;

                case EventType::buttonPress:
                    for (auto& listener : listeners_buttonPress) {
                        listener(getEvent());
                    }
                    break;

                case EventType::buttonRelease:
                    for (auto& listener : listeners_buttonRelease) {
                        listener(getEvent());
                    }
                    break;

                case EventType::motionNotify:
                    for (auto& listener : listeners_motionNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::enterNotify:
                    for (auto& listener : listeners_enterNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::leaveNotify:
                    for (auto& listener : listeners_leaveNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::focusIn:
                    for (auto& listener : listeners_focusIn) {
                        listener(getEvent());
                    }
                    break;

                case EventType::focusOut:
                    for (auto& listener : listeners_focusOut) {
                        listener(getEvent());
                    }
                    break;

                case EventType::keymapNotify:
                    for (auto& listener : listeners_keymapNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::expose:
                    for (auto& listener : listeners_expose) {
                        listener(getEvent());
                    }
                    break;

                case EventType::graphicsExpose:
                    for (auto& listener : listeners_graphicsExpose) {
                        listener(getEvent());
                    }
                    break;

                case EventType::noExpose:
                    for (auto& listener : listeners_noExpose) {
                        listener(getEvent());
                    }
                    break;

                case EventType::circulateRequest:
                    for (auto& listener : listeners_circulateRequest) {
                        listener(getEvent());
                    }
                    break;

                case EventType::configureRequest:
                    for (auto& listener : listeners_configureRequest) {
                        listener(getEvent());
                    }
                    break;

                case EventType::mapRequest:
                    for (auto& listener : listeners_mapRequest) {
                        listener(getEvent());
                    }
                    break;

                case EventType::resizeRequest:
                    for (auto& listener : listeners_resizeRequest) {
                        listener(getEvent());
                    }
                    break;

                case EventType::circulateNotify:
                    for (auto& listener : listeners_circulateNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::configureNotify:
                    for (auto& listener : listeners_configureNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::createNotify:
                    for (auto& listener : listeners_createNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::destroyNotify:
                    for (auto& listener : listeners_destroyNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::gravityNotify:
                    for (auto& listener : listeners_gravityNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::mapNotify:
                    for (auto& listener : listeners_mapNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::mappingNotify:
                    for (auto& listener : listeners_mappingNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::reparentNotify:
                    for (auto& listener : listeners_reparentNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::unmapNotify:
                    for (auto& listener : listeners_unmapNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::visibilityNotify:
                    for (auto& listener : listeners_visibilityNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::colormapNotify:
                    for (auto& listener : listeners_colormapNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::clientMessage:
                    for (auto& listener : listeners_clientMessage) {
                        listener(getEvent());
                    }
                    break;

                case EventType::propertyNotify:
                    for (auto& listener : listeners_propertyNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::selectionClear:
                    for (auto& listener : listeners_selectionClear) {
                        listener(getEvent());
                    }
                    break;

                case EventType::selectionNotify:
                    for (auto& listener : listeners_selectionNotify) {
                        listener(getEvent());
                    }
                    break;

                case EventType::selectionRequest:
                    for (auto& listener : listeners_selectionRequest) {
                        listener(getEvent());
                    }
                    break;

                default:
                    break;
            }
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
                addRootSelectInput(MotionNotify);
                break;

            case EventType::enterNotify:
                listeners_enterNotify.push_back(listener);
                addRootSelectInput(EnterNotify);
                break;

            case EventType::leaveNotify:
                listeners_leaveNotify.push_back(listener);
                addRootSelectInput(LeaveNotify);
                break;

            case EventType::focusIn:
                listeners_focusIn.push_back(listener);
                addRootSelectInput(FocusIn);
                break;

            case EventType::focusOut:
                listeners_focusOut.push_back(listener);
                addRootSelectInput(FocusOut);
                break;

            case EventType::keymapNotify:
                listeners_keymapNotify.push_back(listener);
                addRootSelectInput(KeymapNotify);
                break;

            case EventType::expose:
                listeners_expose.push_back(listener);
                addRootSelectInput(Expose);
                break;

            case EventType::graphicsExpose:
                listeners_graphicsExpose.push_back(listener);
                addRootSelectInput(GraphicsExpose);
                break;

            case EventType::noExpose:
                listeners_noExpose.push_back(listener);
                addRootSelectInput(NoExpose);
                break;

            case EventType::circulateRequest:
                listeners_circulateRequest.push_back(listener);
                addRootSelectInput(CirculateRequest);
                break;

            case EventType::configureRequest:
                listeners_configureRequest.push_back(listener);
                addRootSelectInput(ConfigureRequest);
                break;

            case EventType::mapRequest:
                listeners_mapRequest.push_back(listener);
                addRootSelectInput(MapRequest);
                break;

            case EventType::resizeRequest:
                listeners_resizeRequest.push_back(listener);
                addRootSelectInput(ResizeRequest);
                break;

            case EventType::circulateNotify:
                listeners_circulateNotify.push_back(listener);
                addRootSelectInput(CirculateNotify);
                break;

            case EventType::configureNotify:
                listeners_configureNotify.push_back(listener);
                addRootSelectInput(ConfigureNotify);
                break;

            case EventType::createNotify:
                listeners_createNotify.push_back(listener);
                addRootSelectInput(CreateNotify);
                break;

            case EventType::destroyNotify:
                listeners_destroyNotify.push_back(listener);
                addRootSelectInput(DestroyNotify);
                break;

            case EventType::gravityNotify:
                listeners_gravityNotify.push_back(listener);
                addRootSelectInput(GravityNotify);
                break;

            case EventType::mapNotify:
                listeners_mapNotify.push_back(listener);
                addRootSelectInput(MapNotify);
                break;

            case EventType::mappingNotify:
                listeners_mappingNotify.push_back(listener);
                addRootSelectInput(MappingNotify);
                break;

            case EventType::reparentNotify:
                listeners_reparentNotify.push_back(listener);
                addRootSelectInput(ReparentNotify);
                break;

            case EventType::unmapNotify:
                listeners_unmapNotify.push_back(listener);
                addRootSelectInput(UnmapNotify);
                break;

            case EventType::visibilityNotify:
                listeners_visibilityNotify.push_back(listener);
                addRootSelectInput(VisibilityNotify);
                break;

            case EventType::colormapNotify:
                listeners_colormapNotify.push_back(listener);
                addRootSelectInput(ColormapNotify);
                break;

            case EventType::clientMessage:
                listeners_clientMessage.push_back(listener);
                addRootSelectInput(ClientMessage);
                break;

            case EventType::propertyNotify:
                listeners_propertyNotify.push_back(listener);
                addRootSelectInput(PropertyNotify);
                break;

            case EventType::selectionClear:
                listeners_selectionClear.push_back(listener);
                addRootSelectInput(SelectionClear);
                break;

            case EventType::selectionNotify:
                listeners_selectionNotify.push_back(listener);
                addRootSelectInput(SelectionNotify);
                break;

            case EventType::selectionRequest:
                listeners_selectionRequest.push_back(listener);
                addRootSelectInput(SelectionRequest);
                break;

            default:
                break;
        }
    }
    