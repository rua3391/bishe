#include "sdk/zTcpClient.h"
#include "ctime"

int main()
{
    zTcpClient client;
    if(!client.init("121.4.253.6", 5005))
        return -1;
    clock_t start = clock(); 
    // std::cout << start << std::endl;
    for(int i = 0; i < 10000; ++i)
    {
        std::string str = "发送10000条消息，此次编号为: " + std::to_string(i);
        client.tcpWrite(str.data(), 0);
        char buffer[MAX_SIZE];
        client.tcpRead(buffer);
        std::cout << "来自服务端: " << buffer << std::endl;
    }
    // clock_t time = clock();

    long time = (clock() - start) / CLOCKS_PER_SEC;
    std::cout << "交互10000条消息共耗时" << time << "秒" << std::endl;
    client.final();
    return 0;
}