#ifndef Z_TCPCLINET_H
#define Z_TCPCLINET_H

#include "zSdk.h"
#include "zSingleton.h"

class zTcpClient
{
    public:
        /**
         * \brief 构造函数
         * 
         */ 
        zTcpClient() : _socketfd(-1){}
        /**
         * \brief 析构函数
         * 
         */ 
        ~zTcpClient() {if(_socketfd != -1)  close(_socketfd);}
        /**
         * \brief 创建socket 
         * \param name 服务器端域名或网址
         * \param port 端口号
         * 
         */
        bool init(const char* name, DWORD port)
        {
            if(_socketfd != -1)
            {
                close(_socketfd);
                _socketfd = -1;
            }
            _ip = name;
            hostent* ip;
            sockaddr_in serveraddr;
            _socketfd = socket(AF_INET, SOCK_STREAM, 0);
            if(_socketfd < 0)
            {
                return false;
            }
            ip = gethostbyname(name);
            if(!ip)
            {
                _socketfd = -1;
                close(_socketfd);
                return false;
            }
            memset(&serveraddr,0,sizeof(serveraddr));
            serveraddr.sin_family = AF_INET;
            serveraddr.sin_port = htons(port);
            memcpy(&serveraddr.sin_addr, ip->h_addr_list[0], ip->h_length);

            if(connect(_socketfd, (sockaddr *)(&serveraddr),sizeof(serveraddr)) != 0)
            {
                perror("connect");
                close(_socketfd);  
                _socketfd = -1; 
                return false;
            }
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
            if(_socketfd == -1)
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
        bool tcpWrite(const char* buffer, DWORD len)
        {
            if(_socketfd == -1)
                return false;
            len = htonl(len);
            char tmpbuffer[len + 4];
            memset(tmpbuffer, 0, sizeof(tmpbuffer));
            memcpy(tmpbuffer, &len, 4);
            memcpy(tmpbuffer + 4, buffer, len);
            if (!_writeN(tmpbuffer,len+4))
                return false;
            return true;
        }
        bool final()
        {
            if(_socketfd != -1)
                close(_socketfd);
            _socketfd = -1;
            return true;
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
                readnum = recv(_socketfd,buffer + offset,left,0);
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
                readnum = send(_socketfd,buffer + offset,left,0);
                if (readnum <= 0) 
                    return false;

                offset += readnum;
                left -= readnum;
            }
            return true;
        }
        /**
         * \brief socket
         * 
         */
        SDWORD _socketfd;
        /**
         * \brief ip地址
         * 
         */
        std::string _ip;
        /**
         * \brief 端口
         * 
         */
        WORD _port;  
};


#endif