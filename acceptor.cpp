#include "acceptor.h"
#include <iostream>

Acceptor::Acceptor(EventLoop* loop){
    _loop = loop;
    _lfd = -1;
}

Acceptor::~Acceptor(){
    if(-1 != _lfd) ::close(_lfd);
}

void Acceptor::setCB(AcceptCallBack cb){
    _cb = cb;
}

bool Acceptor::init(){
    _lfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == _lfd ) return false;

    ::sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = ::htons(12345);

    if(-1 == ::inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)) return false;

    if(-1 == ::bind(_lfd, (::sockaddr*)&addr, sizeof(::sockaddr))) return false;

    if(-1 == ::listen(_lfd, 10)) return false;

    Channel* pchannel = new Channel(_loop, _lfd);
    _loop->setMap(_lfd, pchannel);
    pchannel->setCB(CallBack( 
        [this]()->void{
            ::sockaddr_in addr;
            ::socklen_t len = sizeof(::sockaddr);
            int fd = ::accept(this->_lfd, (::sockaddr*)&addr, &len );

            if(fd != -1){
                std::cout << fd << " connected" << std::endl;
                _cb(fd);
            }
            
        }
    ));   // listenfd callback
    pchannel->enableRead();

    return  true;
}

void Acceptor::start(){
    if(!init()) return;
    std::cout << "server init success" << std::endl;
    _loop->loop();
}