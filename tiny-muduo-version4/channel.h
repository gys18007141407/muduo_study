#ifndef CHANNEL_H
#define CHANNEL_H

#include <functional>
#include <sys/types.h>

class EventLoop;

class Channel{
public:
    typedef std::function<void()> CALLBACK;

    explicit Channel(EventLoop*, int64_t);
    ~Channel();

    void setCallBack(CALLBACK&&);

    void ready();

    uint32_t getRevent();

    uint32_t getEvent();

    int64_t getFd();

    void setEvent(uint32_t);

    void setRevent(uint32_t);

    void setWrite();

    void unsetWrite();

    void run();

private:

    int64_t _fd;

    uint32_t _event;

    uint32_t _revent;

    EventLoop* _loop;

    CALLBACK _callback;

};


#endif