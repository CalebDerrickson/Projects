#include <iostream>
#include "MainApp.hpp"




int main() {

    MainApp mainApp(800, 600, "test");
    if (mainApp.init() != STATE::OKAY) return -1;
    if (mainApp.run() != STATE::OKAY) return -1; 

    if (mainApp.shutdown() != STATE::OKAY) return -1;

    return 0;
}


