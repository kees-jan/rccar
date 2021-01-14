#ifndef TCP_MANAGER_H
#define TCP_MANAGER_H
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>



class TCPManager
{
public:
    ~TCPManager();

    bool GetConnection(int port);

    bool Send(std::string value);

    bool Receive(std::string* value);

    void CloseConnection();
    
private: 
    int         clientSocket = 0;
    std::string clientIp;

};


#endif