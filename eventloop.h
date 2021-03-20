#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <vector>
#include <unordered_map>
#include "epoll.h"

class Channel;

class EventLoop{  // 通过loop类来间接使用poll
public:
    EventLoop();   // 因此在构造函数里面 _poll = new Epoll
    ~EventLoop();

    void loop();  // 每一次loop，在_poll中一次epoll_wait

    void update(int);

    void remove(int);

    void setMap(int, Channel*);  

private:
    std::unordered_map<int,Channel*> fd2channel;
    Epoll* _poll;
};


#endif