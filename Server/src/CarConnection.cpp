#include "CarConnection.h"

#include "Config.h"

CarConnection::CarConnection(std::string ControllerIpadress, int port)
    : ControllerIpadress{ControllerIpadress}, port{port},
      console{new UserInterface()}, platoon{new Platoon()},
      clientConnection{new TCPManager()}, leadingCar{new TCPManager()},
      newCarNeeded{true} {
  if (!clientConnection->StartListening(port)) {
    std::cout << "StartListening on clientport failed\n";
  }
  if (!leadingCar->StartListening(port + 1)) {
    std::cout << "StartListening on leading car port failed\n";
  }
}

CarConnection::~CarConnection() {
  delete console;
  console = nullptr;

  delete platoon;
  platoon = nullptr;

  clientConnection->StopListening();
  delete clientConnection;
  clientConnection = nullptr;

  leadingCar->StopListening();
  delete leadingCar;
  leadingCar = nullptr;
}

std::string CarConnection::GetControllerIpadress() const {
  return ControllerIpadress;
}

int CarConnection::GetPort() const { return port; }

bool CarConnection::GetNewCarNeeded() const { return newCarNeeded; }

void CarConnection::SetNewCarNeeded(bool A_newCarNeeded) {
  newCarNeeded = A_newCarNeeded;
}

void CarConnection::ConnectionSequence() {
  console->writeMessage("Scanning for first car.\n");

  std::string lastCarIpAddress = ControllerIpadress;
  int lastCarPort = port + 1;

  while (true) {
    std::cout << "ConnectionSequence begin" << std::endl;
    clientConnection->GetConnection();

    std::cout << "first car" << std::endl;
    std::string Message;
    if (clientConnection->Receive(&Message)) {

      nlohmann::json helloMsg = nlohmann::json::parse(Message);
      std::string ipAdress = helloMsg["ip"];
      int port = helloMsg["port"];

      nlohmann::json connectionMessage;
      connectionMessage["Conectionmessage"] = "ConnectTo";
      connectionMessage["NewIp"] = lastCarIpAddress;
      connectionMessage["Port"] = lastCarPort;
      std::string message = connectionMessage.dump();
      clientConnection->Send(message);
      leadingCar->GetConnection();
      clientConnection->Receive(&Message);
      std::cout << "connection message = " << Message << std::endl;

      platoon->AddCarToPlatoon(ipAdress);
      console->displayFirstCar(ipAdress);
      lastCarIpAddress = ipAdress;
      lastCarPort = port;

      SetNewCarNeeded(console->addNewCar());

      if (GetNewCarNeeded() == true) {
        nlohmann::json lastCarMess;
        lastCarMess["lastCar"] = false;
        clientConnection->Send(lastCarMess.dump());

        std::cout << "json mess= " << lastCarMess.dump() << std::endl;
        std::cout << "message" << std::endl;
      } else {
        nlohmann::json lastCarMess;
        lastCarMess["lastCar"] = true;
        clientConnection->Send(lastCarMess.dump());
      }
      std::cout << "Press enter to make tcp connection";
      std::cin.ignore();
      std::cin.get();
      // usleep(100000000);
    } else {
      throw std::runtime_error("GetConnection initial message fail");
    }

    if (GetNewCarNeeded() == false) {
      break;
    }
  }

  // if (platoon->checkForCars() == false)
  // {
  //   carConnect(ControllerIpadress);
  //   platoon->addCarToPlatoon(carIp);
  //   console->displayFirstCar(carIp);
  //   console->writeMessage(platoon->GetStringOfipAddresses());
  // }
  // else
  // {
  //   std::string previousCar = platoon->addCarToPlatoon(carIp);
  //   if (previousCar == "0")
  //   {
  //     throw std::range_error("no privius car in platoon");
  //   }
  //   else
  //   {
  //     carConnect(previousCar);
  //     console->displayFollowCar(carIp);
  //     console->writeMessage(platoon->GetStringOfipAddresses());
  //   }
  // }
}

int CarConnection::SendCommandToCars(std::string A_command) {
  if (A_command.empty()) {
    return -1;
  } else {
    if (leadingCar->Send(A_command)) {
      return 0;
    } else {
      return -2;
    }
  }
}