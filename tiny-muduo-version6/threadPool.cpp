#include "threadPool.h"
#include "eventLoop.h"
#include <iostream>

ThreadPool::ThreadPool(EventLoop* loop, int n):_closeAll(false){
    if(n < 1) n = 1;
    _numThreads = n;
    _baseLoop = loop;
    _index = 0;
}

ThreadPool::~ThreadPool(){

    stop();

    for(auto & td : _threads){
        if(td.joinable()) td.join();
    }
}

int ThreadPool::getNumOfThreads(){
    return this->_numThreads;
}

EventLoop* ThreadPool::getNextLoop(){
    EventLoop* next = _baseLoop;
    if(_numThreads > 0){
        if(_index == _numThreads) _index = 0;
        next = _loops[_index++];
    }
    return next;  
}

void ThreadPool::start(){
    
    for(int i = 0; i<_numThreads; ++i){
        _threads.push_back(

            std::thread(
            [this]()->void{

  
                EventLoop* ploop =  new EventLoop;


                {
                    std::lock_guard<std::mutex> g_lock(this->_mt_loops);


                    this->_loops.push_back(ploop);
                }

                while(!this->_closeAll.load(std::memory_order_acquire)){

                    ploop->loop();
                    
                }


            }
            )

        );
    }

}

void ThreadPool::stop(){

    _closeAll.store(true, std::memory_order_release);

}

void ThreadPool::doneThenStop(){

    stop();
    std::cout << "t\nhreadpool is STOPPING ......\n" << std::endl;
    for(auto& thread: _threads){
        if(thread.joinable()) thread.join();
    }
    std::cout << "\nthreadpool STOPPED!\n" << std::endl;

}