#include "channel.h"
#include "eventloop.h"
Channel::Channel(EventLoop* loop, int fd){
    _loop = loop;
    _fd = fd;

    _event = 0;
    _revent = 0;
    _cb = nullptr;
}

Channel::~Channel(){

}

int Channel::getFd(){
    return _fd;
}

int Channel::getEvent(){
    return _event;
}

int Channel::getRevent(){
    return _revent;
}

void Channel::setEvent(int event){
    _event |= event;
}

void Channel::setRevent(int revent){
    _revent |= revent;
}

void Channel::setCB( CallBack cb){
    _cb = cb;
}

void Channel::enableRead(){
    _event |= EPOLLIN;
    _loop->update(_fd);
}

void Channel::handleEvent(){
    _cb();
}