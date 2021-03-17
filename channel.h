
#ifndef CHANNEL
#define CHANNEL
#include "IchannelCB.h"
#include <sys/epoll.h>

class channel{
public:
    channel(int efd, int fd){
        _efd = efd;
        _fd = fd;
    }
    ~channel(){

    }

    void setCB(IchannelCB* cb){
        _cb = cb;
    }

    void setRev(int rev){
        _rev = rev;
    }

    void joinEpoll(){
        epoll_event ev;
        ev.data.ptr = this;
        ev.events |= EPOLLIN ;
        epoll_ctl(_efd, EPOLL_CTL_ADD, _fd, &ev);
    }

    void handleEvent(){
        _cb->abstractCB();  // callback,  _cb is acceptor or tcpConn
    }

private:
    int _efd;
    int _fd;  // each channel for each fd

    int _ev;
    int _rev;

    IchannelCB* _cb;  // callback to who create the channel

};

#endif