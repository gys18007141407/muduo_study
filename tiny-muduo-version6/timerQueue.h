#ifndef TIMERQUEUE_H
#define TIMERQUEUE_H

#include <functional>
#include <set>
#include <vector>

#include "timeStamp.h"

class EventLoop;
class Channel;


// timerfd_create

// int timerfd_create(int clockid, int flags);

// timerfd_create用于创建一个定时器文件。

// 参数clockid可以是CLOCK_MONOTONIC或者CLOCK_REALTIME。

// 参数flags可以是0或者O_CLOEXEC/O_NONBLOCK。

// 函数返回值是一个文件句柄fd。



// timerfd_settime

// int timerfd_settime(int ufd, int flags, const struct itimerspec * utmr, struct itimerspec * otmr);

// 此函数用于设置新的超时时间，并开始计时。

// 参数ufd是timerfd_create返回的文件句柄。

// 参数flags为1代表设置的是绝对时间；为0代表相对时间。

// 参数utmr为需要设置的时间。

// 参数otmr为定时器这次设置之前的超时时间。

// 函数返回0代表设置成功。



//read函数可以读timerfd，读的内容为uint_64，表示超时次数

class Timer{

public:
    typedef std::function<void()> CALLBACK;

    Timer(TimeStamp, int64_t, CALLBACK&&);
    ~Timer();

    void run();

    void moveInterval();

    TimeStamp getTimeStamp();

    bool repeat();

    void closeRepeat();


private:

    TimeStamp _stamp;

    CALLBACK _callback;

    int64_t _interval;

};




class TimerQueue{
public:

    typedef std::function<void()> CALLBACK;
    typedef std::pair<TimeStamp, Timer*> TIMER;

    TimerQueue(EventLoop*);
    ~TimerQueue();

    Timer* addTimer(TimeStamp, int64_t, CALLBACK&&);

    void delTimer(Timer*);

    int64_t getTfd();


private:

    bool insert(Timer*);

    void resetTfd(TimeStamp);

    ::timespec timeDist(TimeStamp);

    std::vector<TIMER> getTriggered(TimeStamp);

    int64_t _tfd;

    Channel* _channel;

    EventLoop* _loop;

    std::set<TIMER> _timers;

};


#endif