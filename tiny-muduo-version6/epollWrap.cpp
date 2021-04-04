#include "epollWrap.h"
#include "channel.h"
#include <unistd.h>


Epoll::Epoll(){
    _efd = ::epoll_create(1);
}

Epoll::~Epoll(){
    if(-1 != _efd) ::close(_efd);
}

void Epoll::poll(std::vector<Channel*>& channels){

    int n = ::epoll_wait(_efd, _evs, MAX_EVENTS, TIMEOUT);

    for(int i = 0; i<n; ++i){
        channels.push_back( static_cast<Channel*>(_evs[i].data.ptr));
        channels.back()->setRevent(_evs[i].events);
    }
}

void Epoll::insert(Channel* cl){

    ::epoll_event ev;
    ev.data.ptr = cl;
    ev.events = cl->getEvent();

    ::epoll_ctl(_efd, EPOLL_CTL_ADD, cl->getFd(), &ev);
}

void Epoll::update(Channel* cl){

    ::epoll_event ev;
    ev.data.ptr = cl;
    ev.events = cl->getEvent();

    ::epoll_ctl(_efd, EPOLL_CTL_MOD, cl->getFd(), &ev);
}

void Epoll::erase(Channel* cl){

    ::epoll_event ev;
    ev.data.ptr = cl;
    ev.events = cl->getEvent();

    ::epoll_ctl(_efd, EPOLL_CTL_DEL, cl->getFd(), &ev);

}