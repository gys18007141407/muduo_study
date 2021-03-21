#include "EventLoop.h"

EventLoop::EventLoop(){
    _poll = new Epoll;
}

EventLoop::~EventLoop(){
    if(!_poll) delete _poll;

    for(auto & p : _fd2pChannel){
        if(!p.second) delete p.second;
    }
}

void EventLoop::loop(){

    while(1){

        std::vector<Channel*> channels;

        _poll->loop(channels);

        if(channels.size() == 0) break;

        for(Channel* P : channels){
            P->handleEvent();
        }
    }
}

void EventLoop::addFd(int fd){
    _poll->addFd( _fd2pChannel[fd] );
}

void EventLoop::removeFd(int fd){
    _poll->removeFd( _fd2pChannel[fd] );

    delete _fd2pChannel[fd];

    _fd2pChannel[fd] = nullptr;
}

void EventLoop::setMapping(Channel* pchannel){
    _fd2pChannel[pchannel->getFd()] = pchannel;
}