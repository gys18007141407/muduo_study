#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <functional>
#include <sys/types.h>
#include "buffer.h"
#include "Iuser.h"

#define MAX_BUF_SIZE 128

class EventLoop;
class Channel;

class TcpConn{

public:

    TcpConn(EventLoop*, int64_t);
    ~TcpConn();

    uint64_t send(std::string);

    void setUser(Iuser* );

    std::string getMsg(int64_t);

    std::string getMsgAll();

    int64_t getFd();

private:

    int64_t readEvent();

    int64_t writeEvent();

    EventLoop* _loop;
    Channel* _channel;
    int64_t _fd;

    Buffer _in;
    Buffer _out;

    Iuser* _user;
};


#endif