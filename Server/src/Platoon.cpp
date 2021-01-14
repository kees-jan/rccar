#include "Platoon.h"

Platoon::Platoon()
{
}

Platoon::~Platoon()
{
  for (Car *car : Cars)
  {
    delete car;
    car = nullptr;
  }
}

bool Platoon::CarsPresent() const
{
  if (Cars.size() == 0)
  {
    return false;
  }

  return true;
}

std::string Platoon::GetStringOfIpAddresses()const
{
  std::string returnString;
  int numberOfCars = Cars.size();
  returnString = "Number of Cars = "
                + std::to_string(numberOfCars)
                + "\n" + "================================\n";

  int count = 0;
  for (Car *car : Cars)
  {
    returnString = returnString
                  + "["+std::to_string(count)
                  + "] ip= "
                  + car->GetIpAddress()
                  + "\n";
    count++;

  }
  return returnString;
}

std::string Platoon::GetIpOfFirstCar() const
{
  if (!CarsPresent())
  {
    return "0";
  }
  else
  {
    Car *car = Cars.at(0);
    return car->GetIpAddress();

  }
}

std::string Platoon::GetIpOfLastCar() const
{
  if (!CarsPresent())
  {
   return "0";

  }
  else 
  {
    Car *car = Cars[Cars.size() - 1];
    return car->GetIpAddress();
  }
}

std::string Platoon::AddCarToPlatoon(std::string A_newCarIp)
{
  std::string lastCarIp = GetIpOfLastCar();
  Car *newCar = new Car(A_newCarIp);

  if (!CheckIfCarIpIsAlreadyPresent(newCar))
  {
    Cars.push_back(newCar);
    lastCarIp = A_newCarIp;
  }

  return lastCarIp;
}

bool Platoon::CheckIfCarIpIsAlreadyPresent(Car *newCar)
{
  for (Car *car : Cars)
  {
    if (newCar->GetIpAddress() == car->GetIpAddress())
    {
      return true;
    }
  }

  return false;
}