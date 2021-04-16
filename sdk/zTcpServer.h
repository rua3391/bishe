#ifndef Z_TCPSERVER_H
#define Z_TCPSERVER_H

#include "zSdk.h"
#include "zSingleton.h"

class zTcpServer : public zSingletonBase<zTcpServer>
{
    public:
        /**
         * \brief 构造函数
         * 
         */
        zTcpServer() : _ip(-1), _port(-1){}
        /**
         * 
         * 
         */
        ~zTcpServer() {close(_listenfd); close(_connectfd);}
        /**
         * \brief 创建socket 
         * \param name 服务器端域名或网址
         * \param port 端口号
         * 
         */
        bool init(DWORD port)
        {
            if(_listenfd != -1)
            {
                close(_listenfd);
                _listenfd = -1;
            }
            _listenfd = socket(AF_INET, SOCK_STREAM, 0);
            if(_listenfd < 0)
                return false;
            
            _serveraddr.sin_family = AF_INET;
            _serveraddr.sin_port = htons(port);
            _serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
            if (bind(_listenfd,reinterpret_cast<sockaddr *>(&_serveraddr),sizeof(_serveraddr)) != 0)
            {
                if(_listenfd != -1)  
                    close(_listenfd);
                return false;
            }

            if (listen(_listenfd,5) != 0 )
            {
                if(_listenfd != -1)  
                    close(_listenfd);
                return false;
            }
            return true;
        }
        /**
         * \brief 接受tcp链接
         * 
         */ 
        bool acceptConnect()
        {
            if(_listenfd == -1)
                return false;
            socklen_t size = sizeof(sockaddr_in);
            _connectfd = accept(_listenfd, reinterpret_cast<sockaddr *>(&_clientaddr), &size);
            if(_connectfd <= 0)
                return false;
            return true;
        }
        /**
         * \brief Tcp读端
         * \param socketfd 套接字
         * \param buffer 数据
         * 
         */
        bool tcpRead(char *buffer)
        {
            if(_connectfd == -1)
                return false;
            SDWORD bufflen = 0;
            if(!_readN(reinterpret_cast<char *>(&bufflen), sizeof(SDWORD)))
                return false;
            bufflen = ntohl(bufflen);
            if(!_readN(buffer, bufflen))
                return false;
            return true;
        }
        /**
         * \brief Tcp写端
         * \param buffer 数据
         * \param len 数据长度
         * 
         */
        bool tcpWrite(const char* buffer, DWORD len = 0)
        {
            if(_connectfd == -1)
                return false;
            size_t buflen;
            if(len == 0)
                buflen = strlen(buffer) + 1;
            else
                buflen = len;
            char tmpbuffer[buflen + 4];
            DWORD netlen = htonl(buflen);
            memset(tmpbuffer, 0, sizeof(tmpbuffer));
            memcpy(tmpbuffer, &netlen, 4);
            memcpy(tmpbuffer + 4, buffer, buflen);
            if (!_writeN(tmpbuffer,buflen + 4))
                return false;
            return true;
        }  
        /**
         * \brief 获取客户端ip
         * 
         */ 
        char *getClientIp(){return inet_ntoa(_clientaddr.sin_addr);}
        /**
         * \brief 关闭listenfd
         * 
         */ 
        void closeListenfd()
        {
            if(_listenfd != -1)
                close(_listenfd);
        }
        /**
         * \brief 关闭clientfd
         * 
         */ 
        void closeClientfd()
        {
            if(_connectfd != -1)
                close(_connectfd);
        }
    private:
        /**
         * \brief 读取n字节
         * \param buffer 数据
         * \param len 读取数据长度
         * 
         */ 
        bool _readN(char *buffer, size_t len)
        {
            SDWORD left = len, offset = 0, readnum = 0;
            while(left > 0)
            {
                readnum = recv(_connectfd,buffer + offset,left,0);
                if (readnum <= 0) 
                    return false;

                offset += readnum;
                left -= readnum;
            }
            return true;
        }
        /**
         * \brief 读取n字节
         * \param buffer 数据
         * \param len 读取数据长度
         * 
         */ 
        bool _writeN(char *buffer, size_t len)
        {
            SDWORD left = len, offset = 0, readnum = 0;
            while(left > 0)
            {
                readnum = send(_connectfd,buffer + offset,left,0);
                if (readnum <= 0) 
                    return false;

                offset += readnum;
                left -= readnum;
            }
            return true;
        }
        /**
         * \brief 监听套接字
         * 
         */ 
        SDWORD _listenfd;
        /**
         * \brief 客户端交互套接字
         * 
         */
        SDWORD _connectfd; 
        /**
         * \brief 服务器ip地址
         * 
         */
        DWORD _ip; 
        /**
         * \brief 端口号
         * 
         */ 
        WORD _port;
        /**
         * \brief 服务器addr信息
         * 
         */ 
        sockaddr_in _serveraddr;
        /**
         * \brief 客户端addr信息
         * 
         */
        sockaddr_in _clientaddr; 
};

#endif