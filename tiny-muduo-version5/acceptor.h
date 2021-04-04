#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <functional>
#include <sys/types.h>

#define LISTENLEN 10

class EventLoop;

class Acceptor{
public:

    typedef std::function<void(int64_t)> ACCEPTORCALLBACK;

    Acceptor(EventLoop*);
    ~Acceptor();

    void start();

    void setCallBack(ACCEPTORCALLBACK&&);

private:

    bool init();

    EventLoop* _loop;

    int64_t _listenFd;

    ACCEPTORCALLBACK _callback;
};




#endif