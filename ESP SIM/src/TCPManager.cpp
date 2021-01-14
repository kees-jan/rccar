#include "../inc/TCPManager.h"

TCPManager::TCPManager(int port, std::string ipAddress) {
  CreateConnection(port, ipAddress);
}

TCPManager::TCPManager(int port) {
  if (GetConnection(port)) {
    std::cout << "Connected with server.";
  } else {
    std::cout << "Connection failed";
  }
}

TCPManager::~TCPManager() { CloseConnection(); }

// PRIVATE
bool TCPManager::GetConnection(int port) {
  if (port > 0) {
    sockaddr_in hint;
    hint.sin_port = htons(port);
    hint.sin_family = AF_INET;

    // Create a socket
    listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1) {
      cerr << "Can't create a socket! Quitting" << endl;
      return false;
    }

    // Bind the ip address and port to a socket
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    bind(listening, (sockaddr *)&hint, sizeof(hint));

    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);

    // Wait for a connection
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    clientSocket = accept(listening, (sockaddr *)&client, &clientSize);
    if (clientSocket < 0) {
      cout << "Can't find client to connect to" << endl;
      return false;
    }
    char host[NI_MAXHOST];    // Client's remote name
    char service[NI_MAXSERV]; // Service (i.e. port) the client is connect on

    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    if (getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST,
                    service, NI_MAXSERV, 0) == 0) {
      cout << host << " connected on port " << service << endl;
    } else {
      inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
      cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }
    cout << "Yo" << endl;
    // Close listening socket
    close(listening);
    return true;
  }
  return false;
}

bool TCPManager::CloseConnection() {
  int i = 0;

  if (close(listening) == 0) {
    i++;
  }

  if (close(clientSocket) == 0) {
    i++;
  }

  if (i > 0) {
    return true;
  }
  return false;
}

// PUBLIC
void TCPManager::CreateConnection(int port, std::string ipAddress) {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    printf("connsction failed!\n");
    // Exception maken (Socket creation failed)
  }

  //    Create a hint structure for the server we're connecting with

  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(port);
  inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
  printf("%s:%d\n", __FUNCTION__, __LINE__);

  //    Connect to the server on the socket
  if (connect(sock, (sockaddr *)&hint, sizeof(hint)) == -1) {
    printf("%s:%d\n", __FUNCTION__, __LINE__);
    std::logic_error("dood");
  }
  clientSocket = sock;
  printf("%s:%d\n", __FUNCTION__, __LINE__);
  //    While loop:

  /*        //        Enter lines of text
          cout << "> ";
          getline(cin, userInput);

          //        Send to server
          int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
          if (sendRes == -1)
          {
              cout << "Could not send to server! Whoops!\r\n";
              continue;
          }

          //        Wait for response
          memset(buf, 0, 4096);
          int bytesReceived = recv(sock, buf, 4096, 0);
          if (bytesReceived == -1)
          {
              cout << "There was an error getting response from server\r\n";
          }
          else
          {
              //        Display response
              cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";
          }*/
}

bool TCPManager::Send(const std::string &message) {
  return Send(message.data(), message.size());
}

bool TCPManager::Send(const char *value, int length) {
  printf("%s:%d\n", __FUNCTION__, __LINE__);
  if (*value != '\0' || value == NULL ||
      length == 0) { // This doesn't look right
    int send = write(clientSocket, value, length);
    if (send < 0) {
      printf("%s:%d\n", __FUNCTION__, __LINE__);
      cout << "Error writing to socket" << endl;
      return false;
    } else {
      printf("%s:%d\n", __FUNCTION__, __LINE__);
      return true;
    }
  }
  return false;
}

bool TCPManager::Receive(char *value) {
  // printf("%s:%d\n", __FUNCTION__,__LINE__);
  char buf[8192] = {0};
  memset(value, 0, 8192);

  std::cout << "Receive buff" << buf << std::endl;
  // if(*value != '\0' || value == NULL)
  //{
  printf("%s:%d\n", __FUNCTION__, __LINE__);
  int bytesReceived = recv(clientSocket, buf, 8192, 0);
  std::cout << "Bytes received: " << bytesReceived << std::endl;
  if (bytesReceived == 0) {
    printf("%s:%d\n", __FUNCTION__, __LINE__);
    return false;
  } else {
    printf("%s:%d\n", __FUNCTION__, __LINE__);
    strncpy(value, buf, 8192);
    return true;
  }
  //}
  // printf("%s:%d\n", __FUNCTION__,__LINE__);
  // return false;
}

void TCPManager::HelemaalNiks() {
  // Das vrij weinig
  // LONELY, SO LONELY
}