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

class TCPManager {
public:
  ~TCPManager();

  bool StartListening(int port);
  bool GetConnection();
  void StopListening();

  bool Send(std::string value);

  bool Receive(std::string *value);

  void CloseConnection();

private:
  int listening = 0;
  int clientSocket = 0;
  std::string clientIp;
};

#endif