#include "acceptor.h"
#include "tcpServer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

Acceptor::Acceptor(EventLoop* loop){
    _loop = loop;

    _lfd = ::socket(AF_INET, SOCK_STREAM, 0);
}

Acceptor::~Acceptor(){

    if(-1 != _lfd) ::close(_lfd);
}

void Acceptor::start(){

    if(!init()) return;

    Channel* pchannel = new Channel(_loop, _lfd);

    _loop->setMapping(pchannel);

    pchannel->setCallBack(
        [this]()->void{

            ::sockaddr_in addr;
            ::socklen_t len = sizeof(::sockaddr);

            int newFd = ::accept(_lfd, (::sockaddr*)&addr, &len);

            if(newFd > 0) this->_callback->newConnection(newFd);

        }
    );
    pchannel->joinEfd();

    _loop->loop();

}

bool Acceptor::init(){

    if(-1 == _lfd) return false;

    ::sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = ::htons(12345);
    if(-1 == ::inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)) return false;

    if(-1 == ::bind(_lfd, (::sockaddr*)&addr, sizeof(::sockaddr))) return false;

    if(-1 == ::listen(_lfd, 10)) return false;

    return true;
}

void Acceptor::setCallBack(TcpServer* cb){
    _callback = cb;
}