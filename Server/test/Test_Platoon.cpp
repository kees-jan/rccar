#include "Test_Platoon.h"

TEST_F(Test_Platoon, carsPresent_empty) 
{
    EXPECT_FALSE(testPlatoon->CarsPresent());
}

TEST_F(Test_Platoon, getIpOfLastCar_no_car)
{
	EXPECT_EQ("0", testPlatoon->GetIpOfLastCar());
}

TEST_F(Test_Platoon, addCarToPlatoon_1) 
{
    EXPECT_FALSE(testPlatoon->CarsPresent());
	EXPECT_EQ("0", testPlatoon->AddCarToPlatoon("111.111.111.111"));
    EXPECT_TRUE(testPlatoon->CarsPresent());
}

TEST_F(Test_Platoon, addCarToPlatoon_2) 
{
	EXPECT_FALSE(testPlatoon->CarsPresent());
	EXPECT_EQ("0", testPlatoon->AddCarToPlatoon("111.111.111.111"));
	EXPECT_TRUE(testPlatoon->CarsPresent());
	EXPECT_EQ("111.111.111.111", testPlatoon->AddCarToPlatoon("222.222.222.222"));
    EXPECT_TRUE(testPlatoon->CarsPresent());
}

TEST_F(Test_Platoon, addCarToPlatoon_3) 
{
    EXPECT_FALSE(testPlatoon->CarsPresent());
	EXPECT_EQ("0", testPlatoon->AddCarToPlatoon("111.111.111.111"));
    EXPECT_TRUE(testPlatoon->CarsPresent());
    EXPECT_EQ("111.111.111.111", testPlatoon->AddCarToPlatoon("222.222.222.222"));
    EXPECT_TRUE(testPlatoon->CarsPresent());
    EXPECT_EQ("222.222.222.222", testPlatoon->AddCarToPlatoon("333.333.333.333"));
}

TEST_F(Test_Platoon, addCarToPlatoon_same_car)
{
	EXPECT_FALSE(testPlatoon->CarsPresent());
	EXPECT_EQ("0", testPlatoon->AddCarToPlatoon("111.111.111.111"));
	EXPECT_TRUE(testPlatoon->CarsPresent());

	EXPECT_EQ("111.111.111.111", testPlatoon->AddCarToPlatoon("111.111.111.111"));
    EXPECT_TRUE(testPlatoon->CarsPresent());
}

TEST_F(Test_Platoon, getIpOfFirstCar_1_car) 
{
	testPlatoon->AddCarToPlatoon("111.111.111.111");
	EXPECT_EQ("111.111.111.111", testPlatoon->GetIpOfFirstCar());
}

TEST_F(Test_Platoon, getIpOfFirstCar_2_cars) 
{
	testPlatoon->AddCarToPlatoon("111.111.111.111");
	testPlatoon->AddCarToPlatoon("222.222.222.222");
	EXPECT_EQ("111.111.111.111", testPlatoon->GetIpOfFirstCar());
}
