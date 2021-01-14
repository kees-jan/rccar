#include "TCPManager.h"

// constructor

// destructor
TCPManager::~TCPManager() {
  CloseConnection();
  StopListening();
}

bool TCPManager::StartListening(int port) {
  if (port > 0) {
    sockaddr_in hint;
    hint.sin_port = htons(port);
    hint.sin_family = AF_INET;

    // Create a socket
    listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1) {
      std::cout << "Can't create a socket! Quitting" << std::endl;
      return false;
    }

    // Bind the ip address and port to a socket
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    bind(listening, (sockaddr *)&hint, sizeof(hint));

    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);

    return true;
  }
  return false;
}

// get
bool TCPManager::GetConnection() {
  // Wait for a connection
  sockaddr_in client;
  socklen_t clientSize = sizeof(client);

  clientSocket = accept(listening, (sockaddr *)&client, &clientSize);
  if (clientSocket < 0) {
    std::cout << "Can't find client to connect to" << std::endl;
    return false;
  }
  char host[NI_MAXHOST];    // Client's remote name
  char service[NI_MAXSERV]; // Service (i.e. port) the client is connect on

  memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
  memset(service, 0, NI_MAXSERV);
  clientIp = host;

  if (getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST,
                  service, NI_MAXSERV, 0) == 0) {
    std::cout << host << " connected on port " << service << std::endl;
  } else {
    inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
    std::cout << host << " connected on port " << ntohs(client.sin_port)
              << std::endl;
  }
  return true;
}

void TCPManager::StopListening() { close(listening); }

// set

// functions
bool TCPManager::Send(std::string value) {
  if (value != "") {
    char valueChar[1024];
    strcpy(valueChar, value.c_str());
    int send = write(clientSocket, valueChar, value.size());
    if (send < 0) {
      std::cout << "Error writing to socket" << std::endl;
      return false;
    } else {
      return true;
    }
  }
  return false;
}
// refrence meegeven
bool TCPManager::Receive(std::string *value) {
  char buf[4096];
  memset(buf, 0, 4096);
  int bytesReceived = recv(clientSocket, buf, 4096, 0);
  if (bytesReceived == 0) {
    std::cout << "bytesReceived == 0\n";
    return false;
  } else {
    std::string valueString(buf);
    *value = valueString;
    std::cout << "Received: " << valueString << '\n';
    return true;
  }
}

void TCPManager::CloseConnection() {
  std::cout << "in CloseConnection" << std::endl;
  int closestatus = close(clientSocket); // hello there
  std::cout << "close status = " << closestatus << std::endl;
}