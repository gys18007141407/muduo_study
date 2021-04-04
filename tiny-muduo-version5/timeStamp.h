
#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <sys/types.h>
#include <iostream>

class TimeStamp{

public:

    static const int kUsPerS = 1000*1000;

    TimeStamp(int64_t n = 0);

    ~TimeStamp();


    static TimeStamp nowTimeStamp();

    static TimeStamp nowAfter(int64_t delay);

    static int64_t nowUs();

    int64_t getCreateUs() const;

    std::string getCreateUs_str() const;

    bool valid();



private:

    int64_t _create_us;

    

};

bool operator<(const TimeStamp& lhs, const TimeStamp& rhs);

bool operator==(const TimeStamp& lhs,const TimeStamp& rhs);



#endif