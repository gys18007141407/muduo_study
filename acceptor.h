#ifndef ACCEPTOR_H
#define ACCEPTOR_H
#include "EventLoop.h"

class TcpServer;

class Acceptor{
public:


    Acceptor(EventLoop*);
    ~Acceptor();

    void setCallBack(TcpServer*);

    void start();

private:

    bool init();

    EventLoop* _loop;

    int _lfd;

    TcpServer* _callback;
};


#endif