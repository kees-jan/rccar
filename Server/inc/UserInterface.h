#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include <iostream>
class UserInterface
{
    public:
    //constructor
    UserInterface();
    //deconstructor
    ~UserInterface();

    //get

    //set

    //funtions


    void displayFirstCar(std::string A_FirstCar);

    void displayFollowCar(std::string A_CarIp);

    void writeMessage(std::string A_message);

    bool addNewCar();

    bool lastCar();
};
#endif