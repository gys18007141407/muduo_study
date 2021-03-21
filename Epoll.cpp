#include "Epoll.h"
#include "EventLoop.h"

Epoll::Epoll(){
    _efd = ::epoll_create(1);
}

Epoll::~Epoll(){
    if(-1 != _efd) ::close(_efd);
}


void Epoll::loop(std::vector<Channel*>& channels){
    int fds = ::epoll_wait(_efd, _evs, 100, 10*1000);

    for(int i = 0; i<fds; ++i){
        channels.push_back( static_cast<Channel*> (_evs[i].data.ptr));
        channels.back()->setRevent(_evs[i].events);
    }
}

void Epoll::addFd(Channel* pchannel){
    ::epoll_event ev;
    ev.data.ptr = pchannel;
    ev.events = pchannel->getEvent();

    ::epoll_ctl(_efd, EPOLL_CTL_ADD, pchannel->getFd(), &ev);
}

void Epoll::removeFd(Channel* pchannel){
    ::epoll_event ev;
    ev.data.ptr = pchannel;
    ev.events = pchannel->getEvent();

    ::epoll_ctl(_efd, EPOLL_CTL_DEL, pchannel->getFd(), &ev);
}