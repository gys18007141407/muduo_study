#ifndef TCPCONN_H
#define TCPCONN_H
#include <iostream>
class IMuduoUser;

class EventLoop;

class TcpConn{
public:


    TcpConn(EventLoop* , int);
    ~TcpConn();

    void setUser(IMuduoUser*);

    int send(const std::string& str);

private:
    EventLoop* _loop;

    int _fd;

    IMuduoUser* _user;
};



#endif