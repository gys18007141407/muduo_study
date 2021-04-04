#include "tcpServer.h"
#include "acceptor.h"
#include "eventLoop.h"
#include "tcpConnection.h"
TcpServer::TcpServer(EventLoop* loop, Iuser* user){
    _loop = loop;
    _user = user;
    _acceptor = nullptr;
}

TcpServer::~TcpServer(){
    if(_acceptor) delete _acceptor;
}

void TcpServer::start(){

    _acceptor = new Acceptor(_loop);
    _acceptor->setCallBack(

        [this](int64_t fd)->void{
            TcpConn* conn = new TcpConn(this->_loop, fd);
            conn->setUser(this->_user);
            this->_user->OnConnect(conn);
        }
    );

    _acceptor->start();

}

void TcpServer::close(){
    _acceptor->~Acceptor();
}