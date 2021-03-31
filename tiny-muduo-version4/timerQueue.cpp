
#include "timerQueue.h"
#include "eventLoop.h"
#include "channel.h"
#include <unistd.h>
#include <cstring>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>

Timer::Timer(TimeStamp stamp, int64_t interval, CALLBACK&& cb) : _stamp(stamp), _interval(interval), _callback(cb){

}

Timer::~Timer(){

}

void Timer::run(){  //timer event
    _callback();
}

TimeStamp Timer::getTimeStamp(){
    return _stamp;
}

void Timer::moveInterval(){
    _stamp = TimeStamp::nowAfter(_interval);
}

bool Timer::repeat(){
    return _interval > 0;
}

void Timer::closeRepeat(){
    _interval = 0;
}








TimerQueue::TimerQueue(EventLoop* loop){  //timerfd manage all timer, when tfd triggered, then there is a timer triggerd

    _loop = loop;

    _tfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);

    _channel = new Channel(_loop, _tfd);
    _loop->setPair(_channel);

    _channel->setCallBack(
        [this]()->void{

            uint32_t event = this->_channel->getRevent();
            if(event & EPOLLIN){  //timerfd read callback : over time triggered

                std::cout << "timerQueue read callback" << std::endl;

                uint64_t num;
                int n = ::read(this->_tfd, &num, sizeof(num));   //num is the number of triggered events

                if(n != sizeof(num)) std::perror("read timerfd error");

                std::vector<TIMER> triggered = this->getTriggered(TimeStamp::nowTimeStamp());

                std::cout << "triggered timer size : " << triggered.size() << std::endl;

                for(auto &p : triggered) p.second->run();  //timer event run

                for(auto &p : triggered){     //repeat event
                    if(p.second->repeat()){
                        p.second->moveInterval();
                        this->insert(p.second);
                    }
                }

                TimeStamp next;

                if(this->_timers.size()) next = this->_timers.begin()->first;

                if(next.valid()) this->resetTfd(next);

            }

            if(event & EPOLLOUT){ //timerfd write callback
                std::cout << "timerQueue write callback" << std::endl;
            }

        }
    );

    _channel->ready();

}

TimerQueue::~TimerQueue(){
    
    if(-1 != _tfd) ::close(_tfd);
}

Timer* TimerQueue::addTimer(TimeStamp stamp, int64_t interval, CALLBACK&& cb){
    Timer* timer = new Timer(stamp, interval, std::move(cb));

    _loop->enPendingQueue(
        [this, timer]()->void{

            //insert


            bool earliest = this->insert(timer);

            if(earliest) resetTfd(timer->getTimeStamp());

            
        }
    );

    return timer;
}

void TimerQueue::delTimer(Timer* timer){

    timer->closeRepeat();

    _loop->enPendingQueue(
        [this, timer]()->void{
            
            //delete
            for(auto &p : this->_timers){
                if(p.second == timer){
                    this->_timers.erase(p);
                    break;
                }
            }
            //this->_timers.erase({timer->getTimeStamp(), timer}); // timestamp has moved interval

        }
    );

}


bool TimerQueue::insert(Timer* timer){  //insert timer

    bool earliest = false;

    if(this->_timers.empty() || timer->getTimeStamp() < this->_timers.begin()->first) earliest = true;

    this->_timers.insert({timer->getTimeStamp(), timer});

    return earliest;
}


void TimerQueue::resetTfd(TimeStamp stamp){  //set timerfd trigger time

    ::itimerspec newv, oldv;

    memset(&newv, 0, sizeof(newv));  //must init otherwise the delay time is Big!!!!

    newv.it_value = this->timeDist(stamp);

    ::timerfd_settime(_tfd, 0, &newv, &oldv);

}


::timespec TimerQueue::timeDist(TimeStamp stamp){  //how far from now to stamp
    ::timespec ts;


    int64_t dist = stamp.getCreateUs() - TimeStamp::nowUs();

    if(dist < 100) dist = 100;

    ts.tv_sec = dist / TimeStamp::kUsPerS;
    ts.tv_nsec = dist % TimeStamp::kUsPerS * 1000;

    return ts;
}


std::vector<TimerQueue::TIMER> TimerQueue::getTriggered(TimeStamp now){
    
    std::vector<TIMER> triggered;

    TIMER temp(now, reinterpret_cast<Timer*> (INT64_MAX));

    auto tail = this->_timers.lower_bound(temp);

    std::copy(this->_timers.begin(), tail, std::back_inserter(triggered));

    this->_timers.erase(this->_timers.begin(), tail);

    return triggered;
}

int64_t TimerQueue::getTfd(){
    return this->_tfd;
}

