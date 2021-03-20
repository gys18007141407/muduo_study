#include "server.h"
#include "tcpConn.h"
Server::Server(EventLoop* loop){
    _loop = loop;
}

Server::Server(){
    _loop = new EventLoop;
}

Server::~Server(){

}

void Server::start(){
    _acceptor = new Acceptor(_loop);

    _acceptor->setCB(AcceptCallBack(
        [this](int fd)->void{
            TcpConn * newConn = new TcpConn(_loop, fd);
        }
    ));
    _acceptor->start();
}