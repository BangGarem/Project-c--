// ================= main.cpp =================
#include <iostream>
#include <ctime>
#include "Player.h"
#include "Enemy.h"

void drawBar(int hp, int maxHp) {
    int w = 20;
    int f = hp * w / maxHp;
    std::cout << "[";
    for (int i = 0; i < w; ++i)
        std::cout << (i < f ? "#" : "-");
    std::cout << "] " << hp << "/" << maxHp << "\n";
}

int main() {
    srand(time(nullptr));

    Player player;
    Enemy enemy;

    while (player.isAlive() && enemy.isAlive()) {
        player.applyStatusEffects();
        if (!player.isAlive()) break;
        player.takeTurn(enemy);

        enemy.applyStatusEffects();
        if (!enemy.isAlive()) break;
        enemy.takeTurn(player);
    }

    return 0;
}