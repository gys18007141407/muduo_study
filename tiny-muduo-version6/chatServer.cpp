#include "chatServer.h"
#include "eventLoop.h"
#include "tcpServer.h"
#include "tcpConnection.h"
#include "timeStamp.h"
#include "threadPool.h"
#include <iostream>


ChatServer::ChatServer(int n){

    _server = nullptr;
    _numThreads = n;

}

ChatServer::~ChatServer(){
    if(_server) delete _server;

}

void ChatServer::start(){

    _server = new TcpServer(_numThreads, this);
    _server->start();

}

void ChatServer::OnConnect(TcpConn* conn){
    std::cout << "server OnConnect " << conn->getFd() << std::endl;
    _timer[conn] = nullptr;
    _count[conn] = 0;
}

void ChatServer::OnComplete(TcpConn* conn){
    std::cout << "server OnComplete " << conn->getFd() << std::endl;
}

void ChatServer::OnMessage(TcpConn* conn){
    std::cout << "server OnMessage " << conn->getFd() << std::endl;

    // conn->send(conn->getMsgAll());

    // if(this->_count[conn]) return;

    // _timer[conn] = _loop->runEvery(1000*1000,    // heart beat
    //     [this, conn]()->void{

    //         ++this->_count[conn];

    //         std::cout << conn->getFd() << " runEvery this is " << this->_count[conn] << std::endl;

    //         if(10 == this->_count[conn]){

    //             std::cout << conn->getFd() << " runEvery finished , erase timer ..." << std::endl;

    //             this->_loop->eraseTimer(this->_timer[conn]);

    //             this->_count[conn] = 0;

    //             return;
    //         }
            
    //     }
    // );

    conn->send2all(conn->getMsgAll());


}


void ChatServer::shutdown(){
    this->_server->close();
}