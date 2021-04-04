
#include "buffer.h"

Buffer::Buffer(){
    _msg = "";
}

Buffer::~Buffer(){

}



void Buffer::remove(int64_t n){
    if(n >= _msg.size()){
        _msg.clear();
    }
    else _msg = _msg.substr(n);
}

std::string Buffer::removeAndGetStr(int64_t n){
    if(n > _msg.size()) n = _msg.size();

    std::string t = _msg.substr(0, n);

    remove(n);

    return t;
}

void Buffer::append(std::string str){
    _msg.append(str);
}

const char* Buffer::data(){
    return _msg.data();
}

void Buffer::clear(){
    remove(_msg.size());
}

uint64_t Buffer::size(){
    return _msg.size();
}