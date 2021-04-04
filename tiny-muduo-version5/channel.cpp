#include "channel.h"
#include "eventLoop.h"
#include <sys/epoll.h>

Channel::Channel(EventLoop* loop, int64_t fd){
    _loop = loop;
    _fd = fd;
    _event = 0;
    _revent = 0;
}

Channel::~Channel(){

}

void Channel::run(){
    _callback();
}

void Channel::ready(){

    _event |= EPOLLIN;
    _loop->insert(_fd);
}

void Channel::setEvent(uint32_t ev){
    _event |= ev;
}

void Channel::setRevent(uint32_t ev){
    _revent |= ev;
}

void Channel::setWrite(){
    _event |= EPOLLOUT;
}

void Channel::unsetWrite(){
    _event &= ~EPOLLOUT;
}

void Channel::setCallBack(CALLBACK&& cb){
    _callback = cb;
}

uint32_t Channel::getEvent(){
    return _event;
}

uint32_t Channel::getRevent(){
    return _revent;
}

int64_t Channel::getFd(){
    return _fd;
}

