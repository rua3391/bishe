#ifndef Z_LOG_H
#define Z_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#include "zType.h"

#define LOGNAME "Engine.log"
#define DEBUG(format, ...) ZH.debug(format, ##__VA_ARGS__)
#define INFO(format, ...) ZH.info(format, ##__VA_ARGS__)
#define ERROR(format, ...) ZH.error(format, ##__VA_ARGS__)
#define FATAL(format, ...) ZH.fatal(format, ##__VA_ARGS__)

//gcc自带宏定义
//__LINE__ 表示该行代码的所在行号
//__FILE__ 表示源文件的文件名
//__DATE__ 表示源文件被编译的日期，格式(月/日/年)
//__TIME__ 表示源文件被编译成目标代码的时间，格式(时:分:秒)
//__STDC__ 表示编译器是否标准，标准时表示常量1，非标准则表示其它数字

class zLog 
{
    public:
        /**
         * \brief 构造函数
         * 
         */
        zLog() {}
        /**
         * \brief 析构函数
         * 
         */
        ~zLog() {}  
    public:
        /**
         * \brief 写debug日志
         * \param format 格式参照printf
         * \param ... 可变长参数列表
         * 
         */ 
        void debug(const char* format, ...)
        {
            char *msg = NULL;
            va_list args;
            va_start(args, format);
            size_t size = sizeof(char) * 1024;
            msg = (char *)malloc(size);
            memset(msg, 0, size);
            vsnprintf(msg, size, format, args);
            logDebug("NMODULE", msg);
            free(msg);
            va_end(args);
        }
        /**
         * \brief 写info日志
         * \param format 格式参照printf
         * \param ... 可变长参数列表
         * 
         */ 
        void info(const char* format, ...)
        {
            char *msg = NULL;
            va_list args;
            va_start(args, format);
            size_t size = sizeof(char) * 1024;
            msg = (char *)malloc(size);
            memset(msg, 0, size);
            vsnprintf(msg, size, format, args);
            logInfo("NMODULE", msg);
            free(msg);
            va_end(args);
        }
        /**
         * \brief 写error日志
         * \param format 格式参照printf
         * \param ... 可变长参数列表
         * 
         */ 
        void error(const char* format, ...)
        {
            char *msg = NULL;
            va_list args;
            va_start(args, format);
            size_t size = sizeof(char) * 1024;
            msg = (char *)malloc(size);
            memset(msg, 0, size);
            vsnprintf(msg, size, format, args);
            logError("NMODULE", msg);
            free(msg);
            va_end(args);
        }
        /**
         * \brief 写fatal日志
         * \param format 格式参照printf
         * \param ... 可变长参数列表
         * 
         */ 
        void fatal(const char* format, ...)
        {
            char *msg = NULL;
            va_list args;
            va_start(args, format);
            size_t size = sizeof(char) * 1024;
            msg = (char *)malloc(size);
            memset(msg, 0, size);
            vsnprintf(msg, size, format, args);
            logFatal("NMODULE", msg);
            free(msg);
            va_end(args);
        }
        /**
         * \brief 获取时间戳
         * \param path 是否是log文件时间戳
         * \return 规格化具体时间戳字符串
         * 
         */ 
        const char* getTime(bool path = false)
        {
            //时间
            char *logpath, *timestamp;
            logpath = (char* )malloc(sizeof(char) * 256);
            timestamp = (char* )malloc(sizeof(char) * 256);
            time_t t;
            time(&t);
            struct tm local;
            localtime_r(&t, &local);
            sprintf(logpath,"%04d-%02d-%02d", local.tm_year + 1900, local.tm_mon + 1, local.tm_mday);
            sprintf(timestamp,"[%04d-%02d-%02d %02d:%02d]", local.tm_year + 1900, local.tm_mon + 1, local.tm_mday, local.tm_hour, local.tm_min);
            if(path)
                return logpath;
            else
                return timestamp;
        }
        /**
         * \brief 写日志操作本身
         * \param msg 拼接完日志类型及所属模块的日志信息
         * 
         */ 
        void writeLog(const char* msg)
        {
            FILE* logfile=NULL;
            char logpath[128] = {0};
            snprintf(logpath, sizeof(logpath), "log/");

            char fname[256];
            memset(fname, 0, sizeof(fname));

            const char* time = getTime(true);
            sprintf(fname,"%s/%s%s", logpath, time, LOGNAME);

            logfile = fopen(fname, "ab");
            if(logfile)
            {
                // 判断文件大小
                if (ftell(logfile) < 5*1024*1024)   // 5M
                {
                    //内容
                    fwrite(msg, 1, strlen(msg), logfile);
                    fclose(logfile);
                }
                else
                {
                    fclose(logfile);
                    remove(fname);
                }
            }
            else
            {
                printf("logfile为空");
            }
        }
        /**
         * \brief 记录debug日志到log文件
         * \param filename 日志所属模块名
         * \param msg 日志具体信息
         * 
         */ 
        void logDebug(const char* filename, const char* msg)
        {
            char str[2048];
            const char* time = getTime();
            sprintf(str, "%s[DEBUG] [%s] %s \n", time, filename, msg);
            writeLog(str);
            printf("%s[DEBUG] [%s] %s \n", time, filename, msg);
        }
        /**
         * \brief 记录info日志到log文件
         * \param filename 日志所属模块名
         * \param msg 日志具体信息
         * 
         */ 
        void logInfo(const char* filename, const char* msg)
        {
            char str[2048];
            const char* time = getTime();
            sprintf(str, "%s[INFO] [%s] %s \n", time, filename, msg);
            writeLog(str);
            printf("%s[INFO] [%s] %s \n", time, filename, msg);
        }
        /**
         * \brief 记录error日志到log文件
         * \param filename 日志所属模块名
         * \param msg 日志具体信息
         * 
         */ 
        void logError(const char* filename, const char* msg)
        {
            char str[2048];
            const char* time = getTime();
            sprintf(str, "%s[ERROR] [%s] %s \n", time, filename, msg);
            writeLog(str);
            printf("%s[ERROR] [%s] %s \n", time, filename, msg);
        }
        /**
         * \brief 记录fatal日志到log文件
         * \param filename 日志所属模块名
         * \param msg 日志具体信息
         * 
         */ 
        void logFatal(const char* filename, const char* msg)
        {
            char str[2048];
            const char* time = getTime();
            sprintf(str, "%s[FATAL] [%s] %s \n", time, filename, msg);
            writeLog(str);
            printf("%s[FATAL] [%s] %s \n", time, filename, msg);
        }
};

namespace 
{
    zLog ZH;
}

#endif
