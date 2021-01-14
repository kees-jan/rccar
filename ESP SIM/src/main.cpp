#include <iostream>
#include <stdexcept>

#include "../inc/TCPManager.h"
#include "../inc/Config.h"
#include "../inc/json.hpp"
using json = nlohmann::json;

// client 1

// STATE 
typedef enum
{
    CONNECT,
    SEND,
    RECEIVE,
    DISCONNECT
}STATE;
 
// Variables
 
// Functions

// Main
int main(void)
{
    // Main variables
    //STATE state = CONNECT;
    printf("%s:%d\n", __FUNCTION__,__LINE__);
    char commands[8192];
    //const int serverPort = 4234;
    //bool quit = false;
    //TCPManager* nodeMCU;
    
    // Start code
    std::cout << "\nBooting up..." << std::endl;

    // Connect to server
    TCPManager* server = new TCPManager(PORT, COMPUTERIP, true);
    printf("%s:%d\n", __FUNCTION__,__LINE__);
    char valueChar[1024];
    std::string ownip = OWNIP;
    strcpy(valueChar, ownip.c_str()); 
    server->Send(valueChar, sizeof(valueChar));
    std::cout << "Message Send" << std::endl;
    std::string ip;
    try
    {
        // Wait for NMCU port
        while(!server->Receive(commands));
        //port = (int)commands;      
        auto j3 = json::parse(commands);
        ip=j3["NewIp"];
        std::cout << "IP:" << ip << std::endl;
    }
    catch (const std::exception &exc)
    {
        std::cerr << exc.what();
    }


    ///Commands komt binnen
    
    std::cout << "Received port: " << commands << std::endl;
    std::cout << "old port = " << PORT << " new port = " << PORT+1 << std::endl;
    TCPManager* serverRetry = new TCPManager(PORT+1, ip, true);
    char retrymsg[] = "I am connected to the car";
    printf("%s:%d\n", __FUNCTION__,__LINE__);
    server->Send(retrymsg, sizeof(retrymsg));
    printf("%s:%d\n", __FUNCTION__,__LINE__);
    serverRetry->HelemaalNiks();
    printf("%s:%d\n", __FUNCTION__,__LINE__);
    char messRec[8192];
    std::cout << "mess before reseaved= " << messRec << std::endl;
    server->Receive(messRec);
    server->CloseConnection();
    std::cout << "mess reseaved= " << messRec << std::endl;
    auto connectMess = json::parse(messRec);
    bool lastCar=connectMess["lastCar"];
    if(lastCar)
    {
        while(true)
        {
         char mess[100]={0};
         serverRetry->Receive(mess);
         std::cout << "message = " << mess << std::endl;
        // Don't stop me now ~ Queen
        }
	}
    else
    {
        TCPManager* nextCar = new TCPManager(PORT+1, ip, false);
        while(true)
        {
         char mess[100]={0};
         serverRetry->Receive(mess);
         std::cout << "message = " << mess << std::endl;
         nextCar->Send(mess,sizeof(mess));
        }
	}

    while(true)
    {

        // Don't stop me now ~ Queen
    }

    // While connected to the NMCU. TODO: This is an infinite loop, I don't like it...
    /*while(!quit)
    {
        switch (state)
        {
        case CONNECT:
            if(PORT != serverPort)
            {
                nodeMCU = new TCPManager(PORT, IP, true);
                delete server;
                server = nullptr;
            }
            state = RECEIVE;
            break;
        
        case SEND:
            if(!nodeMCU->Send(commands, sizeof(commands)/sizeof(char)))
            {
                state = RECEIVE;
            }

            if(!server->Send(commands, sizeof(commands)/sizeof(char)))
            {
                state = RECEIVE;
            }
            break;
        
        case RECEIVE:
            if(nodeMCU->Receive(commands))
            {
                state = SEND;
            }
            
            if(server->Receive(commands))
            {
                state = SEND;
            }
            break;

        case DISCONNECT:
            delete nodeMCU;
            nodeMCU = nullptr;
            std::cout << "Disconnected from nodeMCU." << std::endl;
            delete server;
            server = nullptr;
            std::cout << "Disconnected from server." << std::endl;
            quit = true;
            break;

        default:
            std::cout << "How did you get out of the states?\n";
            state = DISCONNECT;
            break;
        }
    }*/
}