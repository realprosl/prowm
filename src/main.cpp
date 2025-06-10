#include "x11++/key.hpp"
#include <x11++/eventType.hpp>
#include<x11++/server.hpp>
#include<iostream>



int main(){
    auto server = x::Server();
    if(!server.connect()) return 1;

    server.addRootEventListener(x::EventType::keyPress, [&](x::Event* event){
        std::cout << "keyPress\n"; 
        if(key::is_Q(*event) || key::is_q(*event)) server.quit();
    });

    server.addRootEventListener(x::EventType::buttonPress, [&](x::Event* event){
        std::cout << "buttonPress\n"; 
    });
    server.listen();
    return 0;
}