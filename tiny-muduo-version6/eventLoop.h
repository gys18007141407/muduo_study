#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <functional>
#include <vector>
#include <unordered_map>
#include <sys/eventfd.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>

class Epoll;
class TimerQueue;
class Timer;
class TimeStamp;
class Channel;
class TcpConn;

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



    const std::thread::id _tid;

    void runInLoop(CALLBACK&&);

    bool _callingPending;

    void addConn(int64_t, TcpConn*);

    static std::list<TcpConn*> _conns;

    static std::mutex _mt_conns;

    static std::unordered_map<int64_t, TcpConn*> _fd2conn;


private:

    std::vector<CALLBACK> _pendingTasks;

    std::unordered_map<int64_t, Channel*> _fd2channel;

    Epoll* _poll;

    TimerQueue* _timerQueue;

    int64_t _eventfd;

    std::mutex _mt_pendingTask;

    std::mutex _mt_loop;


    

};



#endif