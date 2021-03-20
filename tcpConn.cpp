#include "tcpConn.h"
#include <iostream>
TcpConn::TcpConn(EventLoop* loop, int fd){
    _loop = loop;
    _fd = fd;

    Channel *pchannel = new Channel(_loop, _fd);
    _loop->setMap(_fd, pchannel);

    pchannel->setCB(CallBack(
        [this]()->void{
            char buffer[1024];
            int nr = ::read(_fd, buffer, 1024);

            std::cout << "read " << nr << " bytes from " << _fd << std::endl;

            if(0 == nr){
                _loop->remove(_fd);
            }

            int nw = ::write(_fd, buffer, nr);
            std::cout << "write " << nw << " bytes to " << _fd << std::endl;
        }
    ));
    pchannel->enableRead();

}