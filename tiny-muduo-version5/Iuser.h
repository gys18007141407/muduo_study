#ifndef IUSER_H
#define IUSER_H
#include <string>

class TcpConn;

class Iuser{
public:
    virtual void OnMessage(TcpConn*) = 0;

    virtual void OnConnect(TcpConn*) = 0;

    virtual void OnComplete(TcpConn*) = 0;

};


#endif