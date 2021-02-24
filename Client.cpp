#include "sdk/zTcpClient.h"

int main()
{
    zTcpClient client;
    client.init("121.4.253.6", 5005);
    char buffer[2048];
    client.tcpRead(buffer);
    std::cout << buffer << std::endl;
    client.final();
    return 0;
}