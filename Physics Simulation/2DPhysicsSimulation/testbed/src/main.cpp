#include <iostream>
#include "MainApp.hpp"




int main() {

    MainApp mainApp(800, 600, "test");
    mainApp.init();
    mainApp.run();

    mainApp.shutdown();

    return 0;
}


