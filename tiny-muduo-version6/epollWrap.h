#ifndef EPOLLWRAP_H
#define EPOLLWRAP_H

#define MAX_EVENTS 64
#define TIMEOUT (30*1000)

#include <sys/epoll.h>
#include <vector>

class Channel;
class Epoll{
public:

    Epoll();
    ~Epoll();

    void poll(std::vector<Channel*>& );

    void insert(Channel*);

    void update(Channel*);

    void erase(Channel*);

private:

    int _efd;

    ::epoll_event _evs[MAX_EVENTS];

};





#endif