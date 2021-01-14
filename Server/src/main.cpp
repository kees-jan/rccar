#include <Config.h>
#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>

#include <json.hpp>

// for convenience
using json = nlohmann::json;
#include "CarConnection.h"
// #include "ThreadManager.h"

using namespace std;
TCPManager espConnection;
TCPManager espConnectionLeadCar;
CarConnection *carconnection = new CarConnection(OWNIP, PORT);

int main() {
  carconnection->ConnectionSequence();
  while (1) {
    std::cout << "type mesage to send to car\n";
    std::string replyString;
    std::cin >> replyString;
    carconnection->SendCommandToCars(replyString);
    std::cout << "exit funtion " << std::endl;
  }

  // espConnectionLeadCar.GetConnection(6010);
  // char
  // IncommingMessage[]="{\"Conectionmessage\":\"connecting\",\"ip\":123456}";
  // bool success=espConnectionLeadCar.Receive(IncommingMessage);
  // json j = json::parse(IncommingMessage);
  // string printstring=j["Conectionmessage"].get<string>();
  // int ip=j["ip"].get<int>();
  // cout << "json value Conectionmessage= ";
  // cout <<  printstring;
  // cout << "\njson value ip= ";
  // cout <<ip;
  // char x;
  // cin >> x;
  // if(success)
  // {

  // }
  // else
  // {

  // }
}