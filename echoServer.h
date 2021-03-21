#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include "IMuduoUser.h"
#include "EventLoop.h"
#include "tcpConn.h"
#include "tcpServer.h"

class EchoServer:public IMuduoUser{
public:
    EchoServer(EventLoop*);
    ~EchoServer();

    void onMessage(TcpConn*, char*, int);

    void onConnection(TcpConn*);

    void start();

private:
    TcpServer* _server;
    EventLoop* _loop;
};



#endif