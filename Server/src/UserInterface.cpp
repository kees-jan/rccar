#include "UserInterface.h"

UserInterface::UserInterface() {}

UserInterface::~UserInterface() {}

void UserInterface::displayFirstCar(std::string A_FirstCarIp) {
  std::cout << "First car is car ip= " << A_FirstCarIp << "\n";
}

void UserInterface::displayFollowCar(std::string A_CarIp) {
  std::cout << "follow car =  " << A_CarIp << "\n";
}

void UserInterface::writeMessage(std::string A_message) {
  std::cout << A_message << "\n";
}

bool UserInterface::addNewCar() {
  while (true) {
    std::cout << "do you want to connect a new car? [Yes][No]\n";
    std::string replyString;
    std::cin >> replyString;
    if (replyString == "Yes" || replyString == "yes" || replyString == "YES" ||
        replyString == "Y" || replyString == "y") {
      return true;
    } else if (replyString == "No" || replyString == "no" ||
               replyString == "NO" || replyString == "N" ||
               replyString == "n") {
      return false;
    } else {
      std::cout << "did not recognise your answer\n";
    }
  }
}