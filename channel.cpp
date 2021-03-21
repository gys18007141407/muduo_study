
#include "channel.h"
#include "EventLoop.h"


Channel::Channel(EventLoop* loop, int fd){
    _loop = loop;
    _fd = fd;
}

Channel::~Channel(){

}

int Channel::getFd(){
    return _fd;
}

int Channel::getRevent(){
    return _revent;
}

int Channel::getEvent(){
    return _event;
}

void Channel::setEvent(int event){
    _event |= event;
}

void Channel::setRevent(int revent){
    _revent |= revent;
}

void Channel::setCallBack(ChannelCallBack cb){
    _callback = cb;
}

void Channel::handleEvent(){
    _callback();
}

void Channel::joinEfd(){
    _event |= EPOLLIN;

    _loop->addFd(_fd);
}