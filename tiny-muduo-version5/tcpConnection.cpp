#include "tcpConnection.h"
#include "channel.h"
#include "eventLoop.h"
#include <unistd.h>
#include <sys/epoll.h>
#include <iostream>

TcpConn::TcpConn(EventLoop* loop, int64_t fd){
    _loop = loop;
    _fd = fd;

    _channel = new Channel(loop, fd);
    _loop->setPair(_channel);

    _channel->setCallBack(
        [this]()->void{

            uint32_t ev = this->_channel->getRevent();

            if(ev & EPOLLIN){

                std::cout << this->_fd << " EPOLLIN" << std::endl;
                
                this->readEvent();
            }

            if(ev & EPOLLOUT){

                std::cout << this->_fd << " EPOLLOUT" << std::endl;

                this->writeEvent();

            }

        }
    );

    _channel->ready();
}

TcpConn::~TcpConn(){

}



uint64_t TcpConn::send(std::string msg){  // split into two situation

    //server don not know threads
    //so here i add the mission into threadpool
    //I will set tid to flag this tcpconn belonging to which thread
    //if the thread which has the real tid will excute this
    //otherwise it will repush the task into threadpool

    if(std::this_thread::get_id() == _loop->_tid) return sendInLoop(msg);   // prior send function
    else{
        
        _loop->runInLoop(std::bind(&TcpConn::sendInLoop, this, msg));  // new situation : let other thread call sendInLoop
    }

    

    return 0; //return value does not need?

}


uint64_t TcpConn::sendInLoop(std::string msg){

    int64_t n = 0;

    if(0 == _out.size()){

        n = ::write(_fd, msg.c_str(), msg.size());

    }

    if(n < msg.size()){

        _out.append(msg);

        _channel->setWrite();
    }else{
 
        _loop->enPendingQueue(
            [this]()->void{

                this->_user->OnComplete(this);  // why run oncomplete callback in pendingQueue instead of run callback right now
            }
        );
    }

    return n;

}








int64_t TcpConn::readEvent(){

    char buf[MAX_BUF_SIZE];

    int64_t n = ::read(_fd, buf, MAX_BUF_SIZE);

    std::cout << "recv from " << _fd << " bytes " << n << std::endl;

    if(n < 0 && errno == EAGAIN){

        std::cout << "EAGAIN" << std::endl;

    }
    else if(n == 0 || n < 0) {

        std::cout << "erase " << _fd << std::endl;
        _loop->erase(_fd);

    }
    else{

        _in.append(std::string(buf, n));

        _user->OnMessage(this);  // why run oncomplete callback in pendingQueue instead of run callback right now

    }

    return n;

}


int64_t TcpConn::writeEvent(){

    int64_t n = ::write(_fd, _out.data(), _out.size());

    if(n < 0 && errno == EINTR){

        std::cout << "EINTR" << std::endl;

    }
    else if(n <= 0){

        std::cout << "erase " << _fd << std::endl;
        _loop->erase(_fd);

    }
    else{
        
        _out.remove(n);

        if(n == _out.size()) {

            _channel->unsetWrite();

            _loop->enPendingQueue(

                [this]()->void{
                    this->_user->OnComplete(this);
                }

            );

            //_user->OnComplete(this); // why run oncomplete callback in pendingQueue instead of run callback right now
            
        }

        //else keep watch EPOLLOUT

    }

    return n;

}


void TcpConn::setUser(Iuser* user){
    _user = user;
}

std::string TcpConn::getMsg(int64_t n){
    return _in.removeAndGetStr(n);
}

std::string TcpConn::getMsgAll(){
    return _in.removeAndGetStr(_in.size());
}

int64_t TcpConn::getFd(){
    return _fd;
}