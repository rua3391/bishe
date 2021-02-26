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
        zSnowFlake() : _sequenceMask(0b1111111111111111111111) {}
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
        void sleepMs(DWORD secs)
        {
            struct timeval tval;
            tval.tv_sec = secs / 1000;
            tval.tv_usec = (secs * 1000) % 1000000; //微秒
            select(0, NULL, NULL, NULL, &tval);
        }
        /**
         * \brief 距离1970年时间戳 ms级
         * \return 时间戳
         * 
         */ 
        QWORD currentTimeMillisec()
        {
            struct timeb tb;
            ftime(&tb);
            return tb.time * 1000 + tb.millitm;
        }
        /**
         * \brief 获取下一毫秒时间戳
         * 
         */ 
        QWORD getNextMsTimeStamp() 
        {
            sleepMs(1);
            return currentTimeMillisec();
        }
        /**
         * \brief 雪花算法生成id, 抛去了主机位, 因为就我一个
         * \return id号
         * 
         */ 
        QWORD generateId() 
        {
            static QWORD lastTimeStamp = 0;//静态变量
            QWORD timeStamp = currentTimeMillisec();
            if (lastTimeStamp == timeStamp) 
            {
                _sequence = (_sequence + 1) & (_sequenceMask); 
                if (_sequence == 0) 
                {
                    timeStamp = getNextMsTimeStamp();
                }
            } 
            else 
            {
                _sequence = 0;
            }
            lastTimeStamp = timeStamp;
            return (timeStamp << 10) | _sequence;    //64位id, 1位符号位, 41位时间戳, 10位主机号省去, 剩余22位全部作为id号
        }
    private:
        /**
         * \brief id最大序列号 超过则与操作结果为0
         * 
         */ 
        DWORD _sequenceMask;
        /**
         * \brief 序列号 
         * 
         */
        DWORD _sequence; 
};

namespace 
{
    zSnowFlake idGenerator;
}

inline QWORD generateId()
{
    return idGenerator.generateId();
}

#endif