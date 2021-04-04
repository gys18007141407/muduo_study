#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <functional>
#include <vector>
#include <unordered_map>
#include <sys/eventfd.h>
#include <thread>
#include <mutex>
#include <condition_variable>
class Epoll;
class TimerQueue;
class Timer;
class TimeStamp;
class Channel;
class ThreadPool;

class EventLoop{
public:

    typedef std::function<void()> CALLBACK;

    EventLoop();
    ~EventLoop();

    void enPendingQueue(CALLBACK&&);

    void setPair(Channel*);

    void loop();

    void insert(int64_t);

    void update(int64_t);

    void erase(int64_t);

    void wakeup();



    Timer* runAt(TimeStamp, CALLBACK&&);

    Timer* runAfter(int64_t, CALLBACK&&);

    Timer* runEvery(int64_t, CALLBACK&&);

    void eraseTimer(Timer*);

    int64_t _listenfd;  //just use to print info




    ThreadPool* _threadpool;

    const std::thread::id _tid;

    void runInLoop(CALLBACK&&);

    bool _callingPending;
private:

    std::vector<CALLBACK> _pendingTasks;

    std::unordered_map<int64_t, Channel*> _fd2channel;

    Epoll* _poll;

    TimerQueue* _timerQueue;

    int64_t _eventfd;

    std::mutex _mt_pendingTask;

    

};



#endif