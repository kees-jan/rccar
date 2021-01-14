#ifndef TEST_CAR_H
#define TEST_CAR_H

#include <string>

#include "gtest/gtest.h"
#include "Car.h"

class Test_Car : public ::testing::Test
{
protected:
  Test_Car()
  {
    
  }

  ~Test_Car() override
  {
    delete testCar;
    testCar = nullptr;
  }

  std::string testIP = "123.456.789.111";
  Car *testCar = new Car(testIP);
};

#endif