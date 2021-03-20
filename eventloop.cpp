#include "eventloop.h"
#include "channel.h"

EventLoop::EventLoop(){
    _poll = new Epoll;
}

EventLoop::~EventLoop(){
    
}


void EventLoop::loop(){
    while(1){

        std::vector<Channel*> channels;
        _poll->poll(channels);

        if(channels.size() == 0){
            break;
        }else{

            for(auto p : channels){
                p->handleEvent();
            }
        }
    }
}
void EventLoop::setMap(int fd, Channel* channel){
    fd2channel[fd] = channel;
}

void EventLoop::update(int fd){
    _poll->update(fd2channel[fd]);
}

void EventLoop::remove(int fd){
    _poll->remove(fd2channel[fd]);
}