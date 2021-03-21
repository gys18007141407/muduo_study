#include "echoServer.h"
#include <iostream>
EchoServer::EchoServer(EventLoop* loop){
    _loop = loop;
}

EchoServer::~EchoServer(){
    if(!_server) delete _server;
}

void EchoServer::start(){
    _server = new TcpServer(_loop);
    _server->setCallBack(this);
    _server->start();
}

void EchoServer::onConnection(TcpConn* tcpConn){
    std::cout << "OnConnection invoked ! do nothing ..." << std::endl;
}

void EchoServer::onMessage(TcpConn* tcpConn, char* buffer, int len){
    std::cout << "OnMessage invoked ! send message back . " << std::endl;
    tcpConn->send(buffer);
    
}