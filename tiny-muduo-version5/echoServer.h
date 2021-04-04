#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include "Iuser.h"
#include <unordered_map>
class TcpConn;
class EventLoop;
class TcpServer;
class Timer;
class ThreadPool;
class EchoServer:public Iuser{
public:

    EchoServer(EventLoop*, int n = 2);
    ~EchoServer();

    void OnConnect(TcpConn*);

    void OnMessage(TcpConn*);

    void OnComplete(TcpConn*);

    void start();

    void shutdown();

private:

    TcpServer* _server;

    std::unordered_map<TcpConn*, Timer*> _timer;

    EventLoop* _loop;

    std::unordered_map<TcpConn*, uint64_t> _count;

    ThreadPool* _threadpool;

    int _numThreads;

};


#endif