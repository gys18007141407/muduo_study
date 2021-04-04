
#include "timeStamp.h"
#include <sys/time.h>

TimeStamp::TimeStamp(int64_t us) : _create_us(us){

}

TimeStamp::~TimeStamp(){

}


int64_t TimeStamp::nowUs(){
    ::timeval ev;
    ::gettimeofday(&ev, nullptr);

    return ev.tv_sec*kUsPerS + ev.tv_usec;
}

TimeStamp TimeStamp::nowTimeStamp(){
    return TimeStamp(TimeStamp::nowUs());
}

TimeStamp TimeStamp::nowAfter(int64_t delay){
    return TimeStamp(TimeStamp::nowUs() + delay);
}

int64_t TimeStamp::getCreateUs() const{
    return _create_us;
}

std::string TimeStamp::getCreateUs_str() const{

    char t[32];

    int64_t s = _create_us / kUsPerS;
    int64_t us = _create_us % kUsPerS;

    snprintf(t, 31, "%ld.%06ld", s, us);

    return t;
}

bool TimeStamp::valid(){
    return _create_us > 0;
}

bool operator<(const TimeStamp& lhs, const TimeStamp& rhs){
    return lhs.getCreateUs() < rhs.getCreateUs();
}

bool operator==(const TimeStamp& lhs, const TimeStamp& rhs){
    return lhs.getCreateUs() == rhs.getCreateUs();
}