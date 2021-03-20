#ifndef SERVER_H
#define SERVER_H

#include "eventloop.h"
#include "acceptor.h"
class Server{
public:
    typedef std::function<void(int)> AcceptCallBack;  //acceptor的回调

    Server(EventLoop* loop);
    Server();
    ~Server();

    void start();  // 创建acceptor， 同时设置acceptor在接受新连接后的回调


private:
    EventLoop* _loop;
    Acceptor* _acceptor;
};



#endif