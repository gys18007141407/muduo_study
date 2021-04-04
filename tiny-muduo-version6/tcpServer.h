#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "Iuser.h"
class Acceptor;
class EventLoop;
class ThreadPool;
class TcpServer{
public:

    TcpServer(int64_t, Iuser*);
    ~TcpServer();

    void start();

    void close();

private:

    Acceptor* _acceptor;

    Iuser* _user;

    EventLoop* _loop;

    ThreadPool* _threadpool;


};

#endif