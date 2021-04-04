#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <atomic>

std::atomic<bool> _sync;

bool valid;

void threadfun(int fd){

    char buffer[64];
    int n = 0;
    while(!_sync.load(std::memory_order_acquire)){
        n = ::read(fd, buffer, 63);
        buffer[n] = '\0';

        if(n == 0){
            std::cerr << "server closed"<< std::endl;
            valid = false;
            return;
        }

        std::cout << buffer << std::endl;
    }

}

int main(){
    
    _sync.store(false);

    int fd = ::socket(AF_INET, SOCK_STREAM, 0);

    if(-1 == fd){
        std::cerr << "socket failed" << std::endl;
        return 0;
    }

    ::sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = ::htons(12345);

    if(-1 == ::inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)) {
        std::cerr << "assign failed" << std::endl;
        return 0;
    }
    
    if(-1 == ::connect(fd, (::sockaddr*)&addr, sizeof(::sockaddr))){
        std::cerr << "connect failed" << std::endl;
        return 0;
    }

    std::cout << fd << " connect server success" << std::endl;

    valid = true;

    std::thread func(threadfun, fd);


    std::string cmd;
    int n = 0;
    while(1){

        std::getline(std::cin, cmd);

        if(cmd == "quit" || !valid) break;

        n = ::write(fd, cmd.c_str(), cmd.size());

    }

    _sync.store(true, std::memory_order_release);

    if(func.joinable()) func.join();



    ::close(fd);


    return 0;
}