#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
class EventLoop;
class ThreadPool{
public:
    typedef std::function<void(void)> TASKTYPE;

    explicit ThreadPool( EventLoop*, int n = 2);
    ~ThreadPool();

    void start();

    void stop();

    void doneThenStop();

    int getNumOfThreads();

    EventLoop* getNextLoop();

private:
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;



    std::vector<std::thread> _threads;

    int _numThreads;

    EventLoop* _baseLoop;

    std::mutex _mt_loops;

    std::vector<EventLoop*> _loops;

    int64_t _index;

    std::atomic<bool> _closeAll;

    std::condition_variable _cond_stop;

    bool hasWaited;
};



#endif