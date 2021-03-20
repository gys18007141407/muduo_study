#ifndef CHANNEL_H
#define CHANNEL_H

#include <functional>
#include <sys/epoll.h>
class EventLoop;

class Channel{

public:
    typedef std::function<void()> CallBack; // channel的回调函数
    
    Channel(EventLoop* loop, int fd);
    ~Channel();

    void setCB(CallBack cb);  //在acceptor中创建listen channel的回调，在tcpconn创建收到消息时的回调

    int getEvent();
    int getRevent();
    int getFd();
    void setEvent(int event);
    void setRevent(int revent);

    void enableRead();     // 使当前channel管理的fd加入efd中，因此调用_loop->update(this), 若_loop中有fd到Channel*的映射，就传递this->_fd
    void handleEvent();  // 调用回调函数

private:
    CallBack _cb;
    EventLoop* _loop;

    int _fd;
    int _event;
    int _revent;

};


#endif