#include "x11++/eventType.hpp"
#include<x11++/server.hpp>
#include<iostream>



int main(){
    auto server = x::Server();
    if(!server.connect()) return 1;

    server.addRootEventListener(x::EventType::keyPress, [&](x::Event* event){
        std::cout << event->xkey.subwindow << "\n";
        std::cout << "keyPress\n"; 
    });

    server.addRootEventListener(x::EventType::buttonPress, [&](x::Event* event){
        std::cout << "buttonPress\n"; 
    });
    server.listen();
    return 0;
}