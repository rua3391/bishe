#ifndef Z_SNOW_FLAKE_H
#define Z_SNOW_FLAKE_H

#include "zType.h"
#include "zNoneCopy.h"
#include <sys/select.h>
#include <sys/timeb.h>
#include <ctime>
#include <iostream>
#include <unistd.h>

class zSnowFlake : public zNoneCopy
{
    public:
        /**
         * \brief 构造函数
         * 
         */
        zSnowFlake() {}
        /**
         * \brief 析构函数
         * 
         */
        ~zSnowFlake() {}
    public:  
        /**
         * \brief 进程睡眠1ms
         * 
         */ 
        static void sleepMs(DWORD secs)
        {
            struct timeval tval;
            tval.tv_sec = secs / 1000;
            tval.tv_usec = (secs * 1000) % 1000000;
            select(0, NULL, NULL, NULL, &tval);
        }
        /**
         * \brief 距离1970年时间戳 ms级
         * \return 时间戳
         * 
         */ 
        static QWORD currentTimeMillisec(){
            struct timeb tb;
            time_t t;
            ftime(&tb);
            return tb.time * 1000 + tb.millitm;
        }
        /**
         * \brief 获取下一毫秒时间戳
         * 
         */ 
        static QWORD getNextMsTimeStamp() 
        {
            sleepMs(1);
            return currentTimeMillisec();
        }
        /**
         * \brief 雪花算法生成id, 抛去了主机位, 因为就我一个
         * \return id号
         * 
         */ 
        static QWORD generateId() {
            static DWORD sequence = 0;
            static QWORD lastTimeStamp = 0;
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
    private:
        /**
         * \brief id最大序列号 超过则与操作结果为0
         * 
         */ 
        static DWORD sequenceMask;
};

DWORD zSnowFlake::sequenceMask = 0b1111111111;

inline QWORD generateId()
{
    return zSnowFlake::generateId();
}
#endif