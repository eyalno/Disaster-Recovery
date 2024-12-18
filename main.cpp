//This file contains the 'main' function. Program execution begins and ends there.
//DisasterRecovery.cpp reads input from file "input.txt"

#include "DisasterRecovery.h"
#include <iostream>


int main() {
    try {
        DisasterRecovery dr;
        dr.run();
    } catch (const std::logic_error& e) {
        std::cout << "Caught a logic_error: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Caught an unknown exception" << std::endl;
    }
    return 0;
}