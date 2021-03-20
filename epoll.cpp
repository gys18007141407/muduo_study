#include "epoll.h"

Epoll::Epoll(){
    _efd = ::epoll_create(1);
}

Epoll::~Epoll(){
    if(-1 != _efd) ::close(_efd);
}


void Epoll::poll(std::vector<Channel*>& channels){
    int fds = ::epoll_wait(_efd, _evs, 100, 10*1000);

    for(int i = 0; i<fds; ++i){
        channels.push_back( static_cast<Channel*>(_evs[i].data.ptr) );
        channels.back()->setRevent(_evs[i].events);
    }
}

void Epoll::update(Channel* newfd){
    ::epoll_event ev;
    ev.data.ptr = newfd;
    ev.events = newfd->getEvent();
    ::epoll_ctl(_efd, EPOLL_CTL_ADD, newfd->getFd(),  &ev);
}

void Epoll::remove(Channel* fd){
    ::epoll_event ev;
    ev.data.ptr = fd;
    ev.events = fd->getEvent();
    ::epoll_ctl(_efd, EPOLL_CTL_DEL, fd->getFd(), &ev);
}