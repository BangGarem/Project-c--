// ================= main.cpp =================
#include <iostream>
#include <ctime>
#include "Game.h"
#include <limits>

void drawBar(int hp, int maxHp) {
    int w = 20;
    int f = hp * w / maxHp;
    std::cout << "[";
    for (int i = 0; i < w; ++i)
        std::cout << (i < f ? "#" : "-");
    std::cout << "] " << hp << "/" << maxHp << "\n";
}

int main() {

    std::cout << "Program started\n";
    srand(time(nullptr));

    Game game;
    game.run();

    // ... inside Game::run(), after printing the result:
    std::cout << "\nPress Enter to continue...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return 0;
}