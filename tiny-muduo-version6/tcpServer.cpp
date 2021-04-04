#include "tcpServer.h"
#include "acceptor.h"
#include "eventLoop.h"
#include "threadPool.h"
#include "tcpConnection.h"
TcpServer::TcpServer(int64_t numThreads,  Iuser* user){
    _loop = new EventLoop;
    _threadpool = new ThreadPool(_loop, numThreads);
    _user = user;
    _acceptor = nullptr;

}

TcpServer::~TcpServer(){
    if(_acceptor) delete _acceptor;
    if(_threadpool) _threadpool->stop();
}

void TcpServer::start(){

    _acceptor = new Acceptor(_loop);
    _acceptor->setCallBack(

        [this](int64_t fd)->void{

            EventLoop* ioLoop = this->_loop;
            ioLoop = this->_threadpool->getNextLoop();
            TcpConn* conn = new TcpConn(ioLoop, fd);
            conn->setUser(this->_user);
            this->_user->OnConnect(conn);
        }
    );
    _threadpool->start();
    _acceptor->start();
    //_threadpool->stop();

    _threadpool->doneThenStop();

}

void TcpServer::close(){
    _acceptor->~Acceptor();
}