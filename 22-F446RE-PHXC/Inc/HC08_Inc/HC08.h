#ifndef __HC08_H
#define __HC08_H

#include "peripheral.h"

#ifdef __cplusplus
extern "C"
{
#endif

class HC08
{
private:
    /* data */
public:
    HC08(/* args */);
    ~HC08();

    void init();
    void begin();

    void send(float pitch,float speed);
};

#ifdef __cplusplus
}
#endif
#endif