#include "MainGame.hpp"

int main() {
    MainGame game(640, 480, "Space Invaders");
    game.init();
    game.run();

    game.shutdown();
}