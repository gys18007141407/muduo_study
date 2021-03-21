

#ifndef CHANNEL_H
#define CHANNEL_H

#include <functional>

class EventLoop;

class Channel{
public:

    typedef std::function<void()> ChannelCallBack;

    Channel(EventLoop*, int);

    ~Channel();

    void setRevent(int);

    void setEvent(int);

    int getFd();

    int getEvent();

    int getRevent();

    void handleEvent();

    void setCallBack(ChannelCallBack);

    void joinEfd();

private:

    int _fd;

    int _event;

    int _revent;

    EventLoop* _loop;
    ChannelCallBack _callback;
};


#endif