#ifndef ICHANNELCB
#define ICHANNELCB
#include <unistd.h>
#include<sys/epoll.h>
class IchannelCB{  // derived by acceptor and tcpConn , 
public:
    virtual void abstractCB() = 0;
};
#endif