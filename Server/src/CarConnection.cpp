#include "CarConnection.h"

CarConnection::CarConnection(std::string ControllerIpadress, int port)
  : ControllerIpadress{ControllerIpadress}
  , port{port}
  , console{new UserInterface()}
  , platoon{new Platoon()}
  , clientConnection{new TCPManager()}
  , leadingCar{new TCPManager()}
  , newCarNeeded{true}
{
}

CarConnection::~CarConnection()
{
  delete console;
  console = nullptr;

  delete platoon;
  platoon = nullptr;

  delete clientConnection;
  clientConnection = nullptr;

  delete leadingCar;
  leadingCar = nullptr;
}

std::string CarConnection::GetControllerIpadress() const
{
  return ControllerIpadress;
}

int CarConnection::GetPort() const
{
  return port;
}

bool CarConnection::GetNewCarNeeded() const
{
  return newCarNeeded;
}

void CarConnection::SetNewCarNeeded(bool A_newCarNeeded)
{
  newCarNeeded = A_newCarNeeded;
} 

void CarConnection::ConnectionSequence()
{
  console->writeMessage("Scanning for first car.\n");
  while (true)
  {
    std::cout << "ConnectionSequence begin" << std::endl;
    clientConnection->GetConnection(port);
    if (platoon->CarsPresent() == false)
    {
        std::cout << "first car" << std::endl;
      std::string Message;
      if (clientConnection->Receive(&Message)) 
      {
        std::string ipAdress(Message);
        nlohmann::json connectionMessage;
        connectionMessage["Conectionmessage"] = "ConnectTo";
        connectionMessage["NewIp"] = ControllerIpadress;
        std::string message = connectionMessage.dump();
        clientConnection->Send(message);
        leadingCar->GetConnection(port+1);
        clientConnection->Receive(&Message);
        std::cout << "connection message = "
                  << Message
                  << std::endl;

        platoon->AddCarToPlatoon(ipAdress);
        console->displayFirstCar(ipAdress);
        SetNewCarNeeded(console->addNewCar());

        if(GetNewCarNeeded()==true)
        {
            nlohmann::json lastCarMess;
            lastCarMess["lastCar"]=false;
            clientConnection->Send(lastCarMess.dump());

            std::cout << "json mess= "
                      << lastCarMess.dump()
                      << std::endl;
            std::cout <<"message" << std::endl;
		    }   
        else
        {
            nlohmann::json lastCarMess;
            lastCarMess["lastCar"]=true;
            clientConnection->Send(lastCarMess.dump());
		}
          delete clientConnection;
          std::cout << "Press anykey make tcp connection";
          std::cin.ignore();
          std::cin.get();
          //usleep(100000000);
         clientConnection = new TCPManager();
      }
      else
      {
        throw std::runtime_error("GetConnection initial message fail");
      }
    }
    else
    {
      std::cout << "carConnect"
                << std::endl;
      CarConnect(platoon->GetIpOfLastCar());

    }

    if (GetNewCarNeeded() == false)
    {
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

int CarConnection::CarConnect(std::string A_ipAdress)
{
  printf("%s:%d\n", __FUNCTION__,__LINE__);
  std::string Message;
  printf("%s:%d\n", __FUNCTION__,__LINE__);
  if (clientConnection->Receive(&Message))
  {
    printf("%s:%d\n", __FUNCTION__,__LINE__);
    std::string ipAdress(Message);
    std::cout << "car ip = " << ipAdress <<std::endl;
    nlohmann::json connectionMessage;
    connectionMessage["Conectionmessage"] = "ConnectTo";
    printf("%s:%d\n", __FUNCTION__,__LINE__);
    connectionMessage["NewIp"] = A_ipAdress;
    std::string message = connectionMessage.dump();
    clientConnection->Send(message);
    clientConnection->Receive(&Message);
    platoon->AddCarToPlatoon(ipAdress);
    console->displayFirstCar(ipAdress);
    SetNewCarNeeded(console->addNewCar());
    if(GetNewCarNeeded()==true)
        {
            nlohmann::json lastCarMess;
            lastCarMess["lastCar"]=false;
            clientConnection->Send(lastCarMess.dump());
            delete clientConnection;
            std::cout << "Press anykey make tcp connection";
            std::cin.ignore();
            std::cin.get();
            //usleep(10000000);
            clientConnection = new TCPManager();
		}
    else
        {
          nlohmann::json lastCarMess;
          lastCarMess["lastCar"]=true;
          clientConnection->Send(lastCarMess.dump());
          delete clientConnection;
		}
    console->writeMessage(platoon->GetStringOfIpAddresses());
    printf("%s:%d\n", __FUNCTION__,__LINE__);

  }
  else
  {
    throw std::runtime_error("GetConnection initial message fail");
  }
  return -1;
}

int CarConnection::SendCommandToCars(std::string A_command)
{
  if(A_command.empty())
  {
      return -1;
	}
  else
  {
    if(leadingCar->Send(A_command))
    {
      return 0;
    }
    else
    {
      return -2;
    } 
	}
}