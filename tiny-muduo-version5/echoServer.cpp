#include "echoServer.h"
#include "eventLoop.h"
#include "tcpServer.h"
#include "tcpConnection.h"
#include "timeStamp.h"
#include "threadPool.h"
#include <iostream>


EchoServer::EchoServer(EventLoop* loop, int n){
    _loop = loop;
    _server = nullptr;
    _numThreads = n;
    _threadpool = new ThreadPool(_numThreads);
    _loop->_threadpool = _threadpool;
}

EchoServer::~EchoServer(){
    if(_server) delete _server;
    if(_threadpool) delete _threadpool;
}

void EchoServer::start(){
    _threadpool->start();
    _server = new TcpServer(_loop, this);
    _server->start();

}

void EchoServer::OnConnect(TcpConn* conn){
    std::cout << "server OnConnect " << conn->getFd() << std::endl;
    _timer[conn] = nullptr;
    _count[conn] = 0;
}

void EchoServer::OnComplete(TcpConn* conn){
    std::cout << "server OnComplete " << conn->getFd() << std::endl;
}

void EchoServer::OnMessage(TcpConn* conn){
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

    _threadpool->add(&TcpConn::send, conn, conn->getMsgAll());   // conn->send(conn->getMsgAll());


}


void EchoServer::shutdown(){
    this->_server->close();
}