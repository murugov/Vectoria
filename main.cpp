#include "Core/Controller.hpp"
#include <iostream>
#include <exception>

int main() {
    try {
        Core::Controller app {};

        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal application error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "An unknown fatal error has occurred!" << std::endl;
        return 1;
    }

    return 0;
}
