#ifndef SERVER
#define SERVER

#include "acceptor.h"
#include "IacceptCB.h"
#include "tcpConn.h"
#include <vector>

class server:public IacceptCB{
public:
    server(){
        _efd = -1;
    }
    ~server(){

    }

    void start(){
        if(-1 == (_efd = ::epoll_create(1))) return;

        acceptor* paccept = new acceptor(_efd);  // set paccept a private variable as same as acceptor and tcpConn
        paccept->setCB(this);  // set acceptor callbak
        paccept->start();


        int fds = 0;
        while(1){
            std::cout << " while again ..." << std::endl;
            fds = epoll_wait(_efd, _evs, 10, 10000);
            std::cout << fds << " event triggers" << std::endl;

            if(0 == fds) break;

            std::vector<channel*> evs;
            for(int i = 0; i<fds; ++i){
                evs.push_back( static_cast<channel*> (_evs[i].data.ptr));
                evs.back()->setRev(_evs[i].events);
            }

            for(int i = 0; i<fds; ++i) evs[i]->handleEvent();
        }



    }

    void acceptCB(int conn){
        tcpConn* p = new tcpConn(_efd, conn);
    }

private:
    int _efd;
    epoll_event _evs[10];


};

#endif