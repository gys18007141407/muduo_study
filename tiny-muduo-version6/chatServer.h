#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "Iuser.h"
#include <unordered_map>
class TcpConn;
class EventLoop;
class TcpServer;
class Timer;

class ChatServer:public Iuser{
public:

    ChatServer(int n = 2);
    ~ChatServer();

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

    int _numThreads;

};


#endif