#ifndef IMUDUOUSER_H
#define IMUDUOUSER_H
#include "tcpConn.h"
class IMuduoUser{
public:
    IMuduoUser(){}
    ~IMuduoUser(){}

    virtual void onMessage(TcpConn*, char*, int) = 0;
    virtual void onConnection(TcpConn*) = 0;

};



#endif