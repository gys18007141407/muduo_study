#include "echoServer.h"

int main(){
    EventLoop loop;
    EchoServer server(&loop);
    server.start();


    return 0;
}