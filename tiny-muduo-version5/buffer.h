#ifndef BUFFER_H
#define BUFFER_H

#include <string>

class Buffer{
public:
    Buffer();
    ~Buffer();

    void append(std::string);

    void remove(int64_t);

    std::string removeAndGetStr(int64_t);

    const char* data();

    void clear();

    uint64_t size();

private:

    std::string _msg;

};

#endif