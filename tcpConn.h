#ifndef TCPCONN_H
#define TCPCONN_H

#include "eventloop.h"
#include <functional>
class TcpConn{
public:
    typedef std::function<void()> CallBack;
    TcpConn(EventLoop* loop, int fd);  //每次构造创建一个channel，设置在这里创建的回调，每个channel管理一个fd
    ~TcpConn();


private:
    EventLoop* _loop;
    int _fd;
    CallBack _cb;
};

#endif