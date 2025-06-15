#include <xpp/event/eventType.hpp>
#include<xpp/server/server.hpp>
#include<xpp/key/keyType.hpp>




int main(){
    auto server = x::Server();
    if(!server.connect()) return 1;

    {
        using namespace key;
        server.keyMap(Control|Shift, "p", [](x::Event* e){});
    }

    server.listen();
    return 0;
}