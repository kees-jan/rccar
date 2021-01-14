#include "Test_Car.h"
#include <stdexcept>

TEST_F(Test_Car, getIpAddress) 
{
  EXPECT_EQ(testIP, testCar->GetIpAddress());
}

TEST_F(Test_Car, getIpAddress_no_ip)
{
  EXPECT_THROW(Car(""), std::invalid_argument);
}