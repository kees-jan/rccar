#ifndef TCP_MANAGER_H
#define TCP_MANAGER_H
#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

class TCPManager {
private:
  int clientSocket = 0;
  int listening;
  bool GetConnection(int port);

public:
  TCPManager(int port, std::string ipAddress);
  TCPManager(int port);
  ~TCPManager();
  bool CloseConnection();
  void CreateConnection(int port, std::string ipAdress);
  bool Send(const char *value, int length);
  bool Send(const std::string &message);
  bool Receive(char *value);
  void HelemaalNiks();
};

#endif