#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "Iuser.h"
class TcpConn;

class ChatServer:public Iuser{
public:
    explicit ChatServer();
    ~ChatServer();



    void OnConnect(TcpConn*);

    void OnMessage(TcpConn*);

    void OnComplete(TcpConn*);


};


#endif