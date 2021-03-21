#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include "channel.h"
#include <vector>
#include <unistd.h>

class Epoll{
public:
    Epoll();
    ~Epoll();


    void loop(std::vector<Channel*>& );

    void addFd(Channel*);

    void removeFd(Channel*);


private:
    int _efd;
    ::epoll_event _evs[100];

};


#endif