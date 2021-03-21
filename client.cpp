#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

int main(){

    int fd = ::socket(AF_INET, SOCK_STREAM, 0);

    if(-1 == fd) return 0;

    ::sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = ::htons(12345);
    if(-1 == ::inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)) return false;

    if(-1 == ::connect(fd, (::sockaddr*)&addr, sizeof(::sockaddr))) return false;

    std::cout << "connect success ..." << std::endl;

    char buffer[1024] = "hello";

    int n = ::write(fd, buffer, 6);

    std::cout << "send " << n << " bytes to server : " << buffer << std::endl;

    n = ::read(fd, buffer, 1024);

    std::cout << "receive " << n << " bytes from server : " << buffer << std::endl;

    ::close(fd);

    return 0;
}