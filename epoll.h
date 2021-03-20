#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include <vector>
#include <unistd.h>
#include "channel.h"

class Epoll{  // 封装所有epoll操作
public:
    Epoll();  // 构造函数中创建efd
    ~Epoll();

    void poll(std::vector<Channel*>& channels);  //一次 epoll_wait

    void update(Channel*);  // 一次 epoll_add

    void remove(Channel*);   // 一次 epoll_del

private:

    int _efd;
    ::epoll_event _evs[100];
};

#endif