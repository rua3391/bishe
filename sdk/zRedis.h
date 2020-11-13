#ifndef Z_REDIS_H
#define Z_REDIS_H

#include "hiredis.h"
#include "zSdk.h"

/**
 * \brief redis类
 * 
 */ 
class zRedis
{
    public:
        /**
         * \brief 构造函数
         * 
         */ 
        zRedis() : _handle(NULL), _ip("127.0.0.1"), _port(6379) {};
        /**
         * \brief 析构函数
         * 
         */
        ~zRedis();
    public:
        /**
         * \brief 获取数据库句柄
         * 
         */
        bool createHandle()
        {
            _handle = redisConnect(_ip, _port);
            if(_handle == NULL || _handle->err)
            {
                ERROR("获取redis句柄失败");
                return false;
            }
            return true;
        }
        /**
         * \brief 放回数据库句柄
         * 
         */
        void putHandle()
        {
            redisFree(_handle);
        }
        /**
         * \brief 执行数据库操作命令
         * \param cmd 命令(set hset等)
         * 
         */
        bool execCommand(const char* cmd) 
        {
            _reply = (redisReply *)redisCommand(this->_handle, cmd);
            if(_reply->type == REDIS_REPLY_ERROR)
                return false;
            freeReplyObject(_reply);
            return true;
        }
        /**
         * \brief 读取数据库内容
         * \param cmd 具体命令
         * 
         */
        char* readFromRedis(const char* cmd)
        {
            redisReply* reply =(redisReply*) redisCommand(this->_handle, cmd);
            std::string value;
            if(reply->type != REDIS_REPLY_NIL){
                value = std::string(reply->str,reply->str + reply->len);
            }
            freeReplyObject(reply);
            return const_cast<char* >(value.c_str());
        }
        /**
         * \brief 数据库是否存在key
         * \param ID key名
         * 
         */ 
        bool isExisted(const char* ID)
        {
            redisReply * reply = (redisReply*)redisCommand(this->_handle,"exists %s",ID);
            bool res = false;
            if(reply->type == REDIS_REPLY_INTEGER){
                if(reply->integer == 1L)
                    res = true;
            }
            freeReplyObject(reply);
            return res;
        }
    private:
        /**
         * \brief 数据库句柄 
         * 
         */
        redisContext *_handle;
        /**
         * \brief 数据库回应消息
         * 
         */
        redisReply *_reply; 
        /**
         * \brief 数据库ip
         * 
         */
        const char* _ip; 
        /**
         * \brief 端口
         * 
         */
        SQWORD _port;  

};

#endif