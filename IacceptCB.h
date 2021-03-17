
#ifndef IACCEPTCB
#define IACCEPTCB
class IacceptCB{  // accept new connection callback
public:
    virtual void acceptCB(int) = 0;
};
#endif