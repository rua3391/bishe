#ifndef C_MODULE_H
#define C_MODULE_H

#include "zSdk.h"
#include "zRedis.h"

/**
 * \brief module基类 
 * 
 */ 
class cModule
{
    public:
        /**
         * \brief 构造函数
         * 
         */ 
        cModule(std::string type) : _type(type), _redis(new zRedis()) { }
        /**
         * \brief 析构函数
         * 
         */ 
        virtual ~cModule() { }
        /**
         * \brief 记录debug日志 写法与printf类似
         * \param foramt 格式
         * \param ... 可变参数列表
         * 
         */
        virtual void debug(const char* format, ...)
        {
            char *msg = NULL;
            va_list args;
            va_start(args, format);
            size_t size = sizeof(char) * 1024;
            msg = (char *)malloc(size);
            memset(msg, 0, size);
            vsnprintf(msg, size, format, args);
            ZH.logDebug(_type.c_str(), msg);
            free(msg);
            va_end(args);
        }
        /**
         * \brief 记录error日志 写法与printf类似
         * \param foramt 格式
         * \param ... 可变参数列表
         * 
         */
        virtual void error(const char* format, ...)
        {
            char *msg = NULL;
            va_list args;
            va_start(args, format);
            size_t size = sizeof(char) * 1024;
            msg = (char *)malloc(size);
            memset(msg, 0, size);
            vsnprintf(msg, size, format, args);
            ZH.logError(_type.c_str(), msg);
            free(msg);
            va_end(args);
        }
        /**
         * \brief 记录fatal日志 写法与printf类似
         * \param foramt 格式
         * \param ... 可变参数列表
         * 
         */
        virtual void fatal(const char* format, ...)
        {
            char *msg = NULL;
            va_list args;
            va_start(args, format);
            size_t size = sizeof(char) * 1024;
            msg = (char *)malloc(size);
            memset(msg, 0, size);
            vsnprintf(msg, size, format, args);
            ZH.logFatal(_type.c_str(), msg);
            free(msg);
            va_end(args);
        }
        /**
         * \brief 记录info日志 写法与printf类似
         * \param foramt 格式
         * \param ... 可变参数列表
         * 
         */
        virtual void info(const char* format, ...)
        {
            char *msg = NULL;
            va_list args;
            va_start(args, format);
            size_t size = sizeof(char) * 1024;
            msg = (char *)malloc(size);
            memset(msg, 0, size);
            vsnprintf(msg, size, format, args);
            ZH.logInfo(_type.c_str(), msg);
            free(msg);
            va_end(args);
        }   
    public:
        /**
         * \brief 序列化
         * 
         */ 
        virtual void serialize(void *out) = 0;
        /**
         * \brief 反序列化
         * 
         */
        virtual void unserialize() = 0;
        /**
         * \brief 释放资源
         * 
         */
        virtual void final() = 0;
    protected:
        /**
         * \brief 保存资源到_redis数据库
         * 
         */
        void saveTo_redis()
        {
            _redis->createHandle();
            std::stringstream os;
            BYTE buffer[MAX_SIZE];
            serialize(buffer);
            os << "HSET " << "Engine " << _type + " " << buffer;
            if(!_redis->execCommand(os.str().c_str()))
            {
                error("_redis数据库写入失败");
            }
            _redis->putHandle();
        }   
        /**
         * \brief 读取当前模块_redis数据库资源
         * 
         */
        const char* readFromRedis()
        {
            _redis->createHandle();
            std::stringstream os;
            char* buffer = (char* )malloc(MAX_SIZE);
            os << "HGET " << "Engine " << _type;
            buffer = _redis->readFromRedis(os.str().c_str());
            if(!buffer)
            {
                error("_redis数据库读出记录失败");
            }
            _redis->putHandle();
            return buffer;
        } 
    private: 
        /**
         * \brief 模块类型
         * 
         */
        std::string _type; 
        /**
         * \brief _redis
         * 
         */ 
        zRedis *_redis;
};

#endif