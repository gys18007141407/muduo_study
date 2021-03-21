#include "tcpConn.h"
#include <iostream>
#include "channel.h"
#include "EventLoop.h"
#include "IMuduoUser.h"

TcpConn::TcpConn(EventLoop* loop, int fd){

    _loop = loop;

    _fd = fd;

    Channel* pchannel = new Channel(_loop, _fd);
    _loop->setMapping(pchannel);

    pchannel->setCallBack(
        [this]()->void{

            char buffer[1024];

            int len = ::read(_fd, buffer, 1024);

            std::cout << "server receive " << len << " bytes from " << _fd << " : " << buffer << std::endl;

            if(len <= 0){

                this->_loop->removeFd(_fd);

            }else{  // user callback
                this->_user->onMessage(this, buffer, len);
            }
        }
    );
    pchannel->joinEfd();
}


TcpConn::~TcpConn(){

}

void TcpConn::setUser(IMuduoUser* user){
    _user = user;
}

int TcpConn::send(const std::string& msg){
    int n = ::write(_fd, msg.c_str(),msg.size()+1);

    std::cout << "server send " << n << " bytes to " << _fd << " : " << msg << std::endl;
}
