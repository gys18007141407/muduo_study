#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){

    int lfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == lfd ) return false;

    ::sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = ::htons(12345);

    if(-1 == ::inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)) return false;

    if(-1 == ::connect(lfd, (::sockaddr*)&addr, sizeof(::sockaddr))) return false;

    std::cout << "success ..." << std::endl;

    char buffer[1024] = "hello";

    for(int i = 0; i<1000000; ++i){

        int nw = ::write(lfd, buffer, 6);

        std::cout << "write " << nw << " bytes : " << buffer << std::endl;

        int nr = ::read(lfd, buffer, 1024);

        std::cout << "read " << nr << " bytes : " << buffer << std::endl;
    }

    ::close(lfd);

    return 0;
}