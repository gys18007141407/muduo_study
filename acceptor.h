#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "eventloop.h"
#include <functional>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class Acceptor{
public:
    typedef std::function<void()> CallBack;
    typedef std::function<void(int)> AcceptCallBack;

    Acceptor(EventLoop*);  // server创建后就创建acceptor， server.start()就是acceptor.start()
    ~Acceptor();

    bool init();

    void start();

    void setCB(AcceptCallBack); // acceptor只负责accept，创建channel是tcpconn的事情，server中创建acceptor接收新连接后的回调


private:
    int _lfd;
    EventLoop* _loop;
    AcceptCallBack _cb;

};



#endif