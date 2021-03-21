#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "tcpConn.h"
#include "acceptor.h"
#include "IMuduoUser.h"
#include <functional>

class TcpServer{
public:
    typedef std::function<void(int)> AcceptorCallBack;

    TcpServer(EventLoop*);

    ~TcpServer();

    void start();

    void setCallBack(IMuduoUser*);

    void newConnection(int);

private:
    EventLoop* _loop;

    Acceptor* _acceptor;

    IMuduoUser* _user;
};


#endif