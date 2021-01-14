#ifndef TEST_PLATOON_H
#define TEST_PLATOON_H

#include "gtest/gtest.h"
#include "Platoon.h"

class Test_Platoon : public ::testing::Test
{
protected:
    virtual ~Test_Platoon()
    {
        delete testPlatoon;
        testPlatoon = nullptr;
    }
    Platoon* testPlatoon = new Platoon();
};

#endif