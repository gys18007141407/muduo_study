#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include "Epoll.h"
#include <unordered_map>

class EventLoop{
public:
    EventLoop();
    ~EventLoop();

    void loop();
    
    void addFd(int);

    void removeFd(int);

    void setMapping(Channel*);

private:

    Epoll* _poll;
    std::unordered_map<int, Channel*> _fd2pChannel;

};



#endif