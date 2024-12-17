#include "DisasterRecovery.h"
#include <iostream>


//check all inserts to map success?

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