#include "interface.h"

#include <iostream>
#include <string>

int main(int32_t argc, char* argv[]) {
    try {
        Interface interface;
        interface.Start(argc, argv);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown Exception" << std::endl;
        return 1;
    }
    std::cerr << "OK" << std::endl;
    return 0;
}