#include "chatServer.h"


int main(){
    
    ChatServer server(2);

    server.start();

    return 0;
}