#ifndef TCPCONN
#define TCPCONN
#include "IchannelCB.h"
#include "channel.h"
#include <iostream>
class tcpConn:public IchannelCB{  // use to create new connection
public:
    tcpConn(int efd, int fd){   // each tcpConn takes charge of a fd(client)
        _efd = efd;
        _fd = fd;


        _pchannel = new channel(_efd, fd);   // create a new connction means a new channel charging the new fd
        _pchannel->setCB(this);
        _pchannel->joinEpoll();
    }


    void abstractCB(){  // channel callback; and it means this client has msg

        char buf[1024];
        int n = ::read(_fd,buf, 1024);

        std::cout << "client send "<< n << " bytes" << std::endl;

        epoll_event ev;
        if(n <= 0) epoll_ctl(_efd,EPOLL_CTL_DEL, _fd, &ev);

        ::write(_fd, buf, n);

    }
private:
    int _efd;
    int _fd;

    channel* _pchannel; // set channel callback
};

#endif