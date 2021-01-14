#include "Car.h"
#include <stdexcept>

Car::Car(std::string ipAddress)
  : ipAddress{ipAddress}
{
  if (ipAddress.empty())
  {
    throw std::invalid_argument("Given ip address is NULL.");
  }

}

Car::~Car()
{
}

std::string Car::GetIpAddress() const
{  
  return ipAddress;
}

