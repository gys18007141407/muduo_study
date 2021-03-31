#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "Iuser.h"
class Acceptor;
class EventLoop;

class TcpServer{
public:

    TcpServer(EventLoop*, Iuser*);
    ~TcpServer();

    void start();

    void close();

private:

    Acceptor* _acceptor;

    Iuser* _user;

    EventLoop* _loop;

};

#endif