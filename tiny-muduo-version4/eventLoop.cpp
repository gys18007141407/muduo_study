
#include "eventLoop.h"
#include "epollWrap.h"
#include "timerQueue.h"
#include "timeStamp.h"
#include "channel.h"
#include <unistd.h>
#include <iostream>

EventLoop::EventLoop(){

    _poll = new Epoll;

    _timerQueue = new TimerQueue(this);

    _eventfd =  ::eventfd(0, EFD_CLOEXEC);

    Channel* eventChannel = new Channel(this, _eventfd);
    _fd2channel[_eventfd] = eventChannel;

    eventChannel->setCallBack(
        [this, eventChannel]()->void{

            uint32_t ev =  eventChannel->getRevent();

            if(ev & EPOLLIN){
                
                //eventfd read callback
                //std::cout << "eventfd read callback\n";
                uint64_t num;
                ::read(this->_eventfd, &num, sizeof(num));


            }

            if(ev & EPOLLOUT){

                //eventfd write callback
                //std::cout << "eventfd write callback\n";

            }

        }
    );

    eventChannel->ready();
    
}

EventLoop::~EventLoop(){

    if(_poll) delete _poll;
    
    if(_timerQueue) delete _timerQueue;
}

void EventLoop::loop(){

    while(true){

        std::vector<Channel*> channels;
        _poll->poll(channels);

        if(channels.size() == 0) break;

        for(Channel* &p : channels){

            //show some info of fd
            if(p->getFd() == this->_eventfd) std::cout << "EventFd triggered" << std::endl;
            else if(p->getFd() == this->_timerQueue->getTfd()) std::cout << "TimerFd triggered" << std::endl;
            else if(p->getFd() == this->_listenfd) std::cout << "ListenFd triggered" << std::endl;
            else std::cout << "io triggerd" << std::endl;

            p->run();

        }

        for(auto& func : _pendingTasks) func(); //do pending event
        _pendingTasks.clear();
    }

}

void EventLoop::enPendingQueue(CALLBACK&& cb){  //pendingevent wakeup eventfd, because no channel io will lead loop break but there are pendingevents want to run
    _pendingTasks.push_back(std::move(cb));
    wakeup();
}

void EventLoop::setPair(Channel* channel){
    _fd2channel[channel->getFd()] = channel;
}

void EventLoop::insert(int64_t fd){
    _poll->insert(_fd2channel[fd]);
}

void EventLoop::update(int64_t fd){
    _poll->update(_fd2channel[fd]);
}

void EventLoop::erase(int64_t fd){
    _poll->erase(_fd2channel[fd]);
}

void EventLoop::wakeup(){
    uint64_t num = 1;
    ::write(_eventfd, &num, sizeof(num));
}




Timer* EventLoop::runAt(TimeStamp when, CALLBACK&& cb){
    return _timerQueue->addTimer(when, 0, std::move(cb));
}

Timer* EventLoop::runAfter(int64_t delay, CALLBACK&& cb){
    return _timerQueue->addTimer(TimeStamp::nowAfter(delay), 0, std::move(cb));
}

Timer* EventLoop::runEvery(int64_t interval, CALLBACK&& cb){
    return _timerQueue->addTimer(TimeStamp::nowTimeStamp(), interval, std::move(cb));
}

void EventLoop::eraseTimer(Timer* timer){
    _timerQueue->delTimer(timer);
}