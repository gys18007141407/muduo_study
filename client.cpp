
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
int main(){
    int _lfd = -1;
    if(-1 == (_lfd = ::socket(AF_INET, SOCK_STREAM, 0))) return 0;

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    if(-1 == ::inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)) return 0;

    if(-1 == ::connect(_lfd, (sockaddr*)&addr, sizeof(sockaddr))) return 0;

    std::cout << "success" << std::endl;

    char buf[1024] = "hello";
    ::write(_lfd, buf, 6);

    int n = ::read(_lfd, buf, 1024);

    std::cout << "server send " << n << " bytes : " << buf << std::endl;

    return 0;
}