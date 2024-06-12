#include "MainGame.hpp"

int main() {
    MainGame game(600, 800, "Space Invaders");
    game.init();
    game.run();

    game.shutdown();
}