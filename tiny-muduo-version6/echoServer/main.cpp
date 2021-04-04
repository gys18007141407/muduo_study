#include "echoServer.h"

int main(){
    
    EchoServer server(2);

    server.start();

    return 0;
}