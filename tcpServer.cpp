#include "tcpServer.h"

TcpServer::TcpServer(EventLoop* loop){
    _loop = loop;
}

TcpServer::~TcpServer(){
    if(!_acceptor) delete _acceptor;
}

void TcpServer::setCallBack(IMuduoUser* user){
    _user = user;
}

void TcpServer::start(){
    _acceptor = new Acceptor(_loop);
    _acceptor->setCallBack(this);
    _acceptor->start();
}

void TcpServer::newConnection(int fd){
    TcpConn* conn = new TcpConn(_loop, fd);
    conn->setUser(_user);
    _user->onConnection(conn);
}