#ifndef ACCEPTOR
#define ACCEPTOR
#include "IchannelCB.h"
#include "IacceptCB.h"
#include "channel.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class acceptor: public IchannelCB{
public:

    acceptor(int efd){
        _efd = efd;
        _lfd = -1;
    }
    ~acceptor(){

    }

    bool init(){
        if(-1 == (_lfd = ::socket(AF_INET, SOCK_STREAM, 0))) return 0;

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(12345);
        if(-1 == ::inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)) return 0;

        if(-1 == ::bind(_lfd, (sockaddr*)&addr, sizeof(sockaddr))) return 0;

        if(-1 == ::listen(_lfd, 5)) return 0;

        return 1;
    }

    void start(){
        if(!init()) return;


        // listen socket join epollfd
        _pchannel = new channel(_efd, _lfd);  
        _pchannel->setCB(this);   // set channel callback
        _pchannel->joinEpoll();
    }


    void setCB(IacceptCB* cb){
        _cb = cb;
    }

    void abstractCB(){  // channel callback ; and it means new conn comes
        sockaddr_in addr;
        socklen_t len = sizeof(sockaddr);
        int conn = ::accept(_lfd, (sockaddr*)&addr, &len);

        if(-1 != conn){
            _cb->acceptCB(conn);  //  connection
        }
    }

private:
    int _efd;
    int _lfd;

    IacceptCB* _cb;
    channel* _pchannel;  // set channel callback
};
#endif