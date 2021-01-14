#ifndef CARCONNECTION_H
#define CARCONNECTION_H
#include "Platoon.h"
#include "TCPManager.h"
#include "UserInterface.h"
#include <bits/stdc++.h>
#include <iostream>
#include <json.hpp>
#include <string>
#include <unistd.h>

class CarConnection {
public:
  CarConnection(std::string A_ControllerIpadress, int A_port);
  ~CarConnection();

  std::string GetControllerIpadress() const;

  int GetPort() const;

  bool GetNewCarNeeded() const;

  void SetNewCarNeeded(bool A_addNewCar);

  void ConnectionSequence();

  // returns 0 for message send
  // returns -1 for invalid imput (empty string)
  // returns -2 for send failed
  int SendCommandToCars(std::string A_command);

private:
  std::string ControllerIpadress;
  int port;
  UserInterface *console;
  Platoon *platoon;
  TCPManager *clientConnection;
  TCPManager *leadingCar;
  bool newCarNeeded;
};

#endif