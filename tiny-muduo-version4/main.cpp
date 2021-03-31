#include "echoServer.h"
#include "eventLoop.h"
#include "Iuser.h"

int main(){

    EventLoop loop;
    
    EchoServer server(&loop);

    server.start();

    loop.loop();

    return 0;
}