#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <Config.h>
#include <string>
#include <thread>

#include <json.hpp>

// for convenience
using json = nlohmann::json;
#include "CarConnection.h"
// #include "ThreadManager.h"

using namespace std;
TCPManager espConnection;
TCPManager espConnectionLeadCar;
CarConnection *carconnection= new CarConnection(OWNIP,4234);

int main()
{   
    carconnection->ConnectionSequence();
    while(1)
    {
        std::cout << "type mesage to send to car\n";
        std::string replyString;
        std::cin >> replyString;
        carconnection->SendCommandToCars(replyString);
        std::cout << "exit funtion " << std::endl;
    }

    //espConnectionLeadCar.GetConnection(6010);
    // char IncommingMessage[]="{\"Conectionmessage\":\"connecting\",\"ip\":123456}";
    //bool success=espConnectionLeadCar.Receive(IncommingMessage);
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