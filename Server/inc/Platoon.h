#ifndef PLATOON_H
#define PLATOON_H
#include <string>
#include <vector>
#include "Car.h"
#include <new> 
#include <bits/stdc++.h>

class Platoon
{
public:
    Platoon();
    ~Platoon();

    //returns a true if vector contains cars
    //else it returns false
    bool CarsPresent() const;

    //returns a sting of all cars in the vector 
    std::string GetStringOfIpAddresses() const;

    //returns the ip of the first car in the vector 
    //if there is no first car it returns "0""
    std::string GetIpOfFirstCar() const;
    
    //returns the ip of the last car in the vector 
    //if there is no car it returns "0""
    std::string GetIpOfLastCar() const;

    //adds car to the platoon vector
    //returns the ip of the previus car if possible
    //else it returns "0"
    std::string AddCarToPlatoon(std::string A_ipOfNewCar);

private:
    std::vector<Car*>   Cars;
    bool                firstCarAdded;

    bool CheckIfCarIpIsAlreadyPresent(Car *newCar);
};

#endif