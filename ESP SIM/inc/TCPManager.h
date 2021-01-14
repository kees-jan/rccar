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

using namespace std;

class TCPManager
{
private: 
    int clientSocket = 0;
    int listening;
    bool GetConnection(int port);
public:
    TCPManager(int port, std::string ipAddress, bool client);
    ~TCPManager();
    bool CloseConnection();
    void CreateConnection(int port, std::string ipAdress);
    bool Send(char* value, int length);
    bool Receive(char* value);
    void HelemaalNiks();
};

#endif