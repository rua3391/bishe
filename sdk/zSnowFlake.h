#ifndef Z_SNOW_FLAKE_H
#define Z_SNOW_FLAKE_H

#include "zType.h"
#include <sys/select.h>
#include <sys/timeb.h>
#include <iostream>

//sleep毫秒级实现
inline void sleepMs(DWORD secs)
{
    struct timeval tval;
    tval.tv_sec = secs / 1000;
    tval.tv_usec = (secs * 1000) % 1000000;
    select(0, NULL, NULL, NULL, &tval);
}

//距离1970年时间戳
inline QWORD currentTimeMillisec(){
	struct timeb tb;
	ftime(&tb);
    std::cout<<tb.time * 1000 + tb.millitm<<std::endl;
	return tb.time * 1000 + tb.millitm;
}

inline QWORD getNextMsTimeStamp() {
    sleepMs(1);
    return currentTimeMillisec();
}

static QWORD lastTimeStamp;
DWORD sequenceMask = 0b1111111111;

inline QWORD getSnowflaksUid() {
    static DWORD sequence;
    // 时间戳
    QWORD timeStamp = currentTimeMillisec();
    if (lastTimeStamp == timeStamp) 
    {
        sequence = (sequence + 1) & (sequenceMask); 
        if (sequence == 0) 
        {
            timeStamp = getNextMsTimeStamp();
        }
    } 
    else 
    {
        sequence = 0;
    }
    lastTimeStamp = timeStamp;
    return (timeStamp << 10) | sequence;
}

#endif