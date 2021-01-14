#ifndef CAR_H
#define CAR_H
#include <string>

class Car
{
public:
    Car(std::string ipAddress);
    ~Car();

    std::string GetIpAddress() const;
    
private:
    std::string ipAddress;

};

#endif