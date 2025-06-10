#include<X11/Xlib.h>
#include<X11/X.h>
#include <functional>
#include<mask.hpp>

namespace x {

    enum class EventType;
    using Event = XEvent;
    using EventCallback = std::function<void(Event*)>;

    class Server{
        public:
            Server(const char* _displayname= nullptr);
            ~Server();
    
            bool connect();
            void disconnect();
            void raiseWindow(Window window);
            void moveAndResizeWindow(Window window, int initx, int inity, unsigned int width, unsigned int height);
            void moveWindow(Window window, int initx, int inity);
            void resizeWindow(Window window, unsigned int width, unsigned int height);
            XWindowAttributes getWindowAttributes(Window window);
            void fillWindowAttributes(Window window, XWindowAttributes* attrs);
            void addRootEventListener(EventType type,EventCallback listener);
            void nextEvent();
            void listen();
            void grabAnyKey(bool condition = false);
            void ungrabAnyButton();
            void ungrabAnyKey();
            void grabAnyButton(bool condition = false);
            Event* getEvent();
    
        private:
            void addRootSelectInput(long evetMask);
            Display* display = nullptr;
            Event event;
            const char* displayname = nullptr;
            MaskBit eventMask;
            std::vector<EventCallback> listeners_keyPress;
            std::vector<EventCallback> listeners_keyRelease;
            std::vector<EventCallback> listeners_buttonPress;
            std::vector<EventCallback> listeners_buttonRelease;
            std::vector<EventCallback> listeners_motionNotify;
            std::vector<EventCallback> listeners_enterNotify;
            std::vector<EventCallback> listeners_leaveNotify;
            std::vector<EventCallback> listeners_focusIn;
            std::vector<EventCallback> listeners_focusOut;
            std::vector<EventCallback> listeners_keymapNotify;
            std::vector<EventCallback> listeners_expose;
            std::vector<EventCallback> listeners_graphicsExpose;
            std::vector<EventCallback> listeners_noExpose;
            std::vector<EventCallback> listeners_circulateRequest;
            std::vector<EventCallback> listeners_configureRequest;
            std::vector<EventCallback> listeners_mapRequest;
            std::vector<EventCallback> listeners_resizeRequest;
            std::vector<EventCallback> listeners_circulateNotify;
            std::vector<EventCallback> listeners_configureNotify;
            std::vector<EventCallback> listeners_createNotify;
            std::vector<EventCallback> listeners_destroyNotify;
            std::vector<EventCallback> listeners_gravityNotify;
            std::vector<EventCallback> listeners_mapNotify;
            std::vector<EventCallback> listeners_mappingNotify;
            std::vector<EventCallback> listeners_reparentNotify;
            std::vector<EventCallback> listeners_unmapNotify;
            std::vector<EventCallback> listeners_visibilityNotify;
            std::vector<EventCallback> listeners_colormapNotify;
            std::vector<EventCallback> listeners_clientMessage;
            std::vector<EventCallback> listeners_propertyNotify;
            std::vector<EventCallback> listeners_selectionClear;
            std::vector<EventCallback> listeners_selectionNotify;
            std::vector<EventCallback> listeners_selectionRequest;
    };
}