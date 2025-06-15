#include<X11/Xlib.h>
#include<X11/X.h>
#include <functional>
#include <map>
#include<xpp/mask/mask.hpp>

namespace x {

    enum class EventType;
    using Event = XEvent;
    using EventCallback = std::function<void(Event*)>;

    class Server{
        public:
            Server(const char* _displayname= nullptr);
            ~Server();
            // create
            bool connect();
            void disconnect();
            void listen();
            void quitLoop();
            // window
            void raiseWindow(Window window);
            void moveAndResizeWindow(Window window, int initx, int inity, unsigned int width, unsigned int height);
            void moveWindow(Window window, int initx, int inity);
            void resizeWindow(Window window, unsigned int width, unsigned int height);
            XWindowAttributes getWindowAttributes(Window window);
            void fillWindowAttributes(Window window, XWindowAttributes* attrs);
            // event
            void allowAllEvents(Event*);
            void addRootEventListener(EventType type,EventCallback listener);
            void nextEvent();
            void grabAnyKey(bool condition = false);
            void ungrabAnyButton();
            void ungrabAnyKey();
            void grabAnyButton(bool condition = false);
            void keyMap(long, std::string, EventCallback);
            // utils
            void flush();
            Event* getEvent();
            template<typename Out >
            Out cast(auto* in){
                return reinterpret_cast<Out>(in);
            }
    
        private:
            void addRootSelectInput(long evetMask);
            void updateEventMaskForRoot(EventType type);
            Display* display = nullptr;
            Event event;
            const char* displayname = nullptr;
            MaskBit eventMask;
            bool stop = false;
            std::map<EventType, std::vector<EventCallback>> eventListeners;
    };
}