#include "acceptor.h"
#include "eventLoop.h"
#include "channel.h"

#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

void show(){
        std::cout << "**********************************************************************************************" << std::endl;
        std::cout << "*             no client connect, CONTINUE ACCEPT new socket connection press c or C          *" << std::endl;
        std::cout << "*                          press any other key will QUIT                                     *" << std::endl;
        std::cout << "**********************************************************************************************" << std::endl;
}

Acceptor::Acceptor(EventLoop* loop){
    _loop = loop;

    _listenFd = ::socket(AF_INET, SOCK_STREAM, 0);

    _loop->_listenfd = _listenFd;
}

Acceptor::~Acceptor(){
    if(-1 != _listenFd) ::close(_listenFd);
}

void Acceptor::start(){
    if(!init()){
        std::perror("server init failed");
        std::cout << strerror(errno) << std::endl;
        return;
    }

    std::cout << "listening ..." << std::endl;

    _channel = new Channel(_loop, _listenFd);
    _loop->setPair(_channel);

    _channel->setCallBack(
        [this]()->void{
            
            ::sockaddr_in addr;
            ::socklen_t len = sizeof(::sockaddr);
            int64_t fd = ::accept(this->_listenFd, (::sockaddr*)&addr, &len);

            if(fd != -1) this->_callback(fd);
        }
    );

    _channel->ready();

    std::string cmd;


    do{

        _loop->loop();

        show();

        std::getline(std::cin, cmd);
        
    }while(cmd == "c" || cmd == "C");

}



void Acceptor::setCallBack(ACCEPTORCALLBACK&& cb){
    _callback = cb;
}

bool Acceptor::init(){

    if(-1 == _listenFd) return false;

    ::sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = ::htons(12345);

    if(-1 == ::inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)) return false;

    if(-1 == ::bind(_listenFd, (::sockaddr*)&addr, sizeof(::sockaddr))) return false;

    if(-1 == ::listen(_listenFd, LISTENLEN)) return false;

    return true;

}