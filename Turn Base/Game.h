#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Player.h"
#include "Enemy.h"

class Game {
public:
    void run() {
        std::cout << "===== turn base rpg ( console version) =====\n";

        Player player;
        Enemy enemy;

        while (player.isAlive() && enemy.isAlive()) {
            std::cout << "\n-----------------------------------\n";
            std::cout << "Player HP:" << player.getHP() << "/" << player.getMaxHP() << "\n";
            std::cout << "Enemy HP:" << enemy.getHP() << "/" << enemy.getMaxHP() << "\n";

            player.applyStatusEffects();
            if (!player.isAlive()) break;
            player.takeTurn(enemy);

            if (!enemy.isAlive()) break;

            enemy.applyStatusEffects();
            enemy.takeTurn(player);
        }

        std::cout << "\n=====================================\n";
        if (player.isAlive())
            std::cout << "Player wins!\n";
        else
            std::cout << "game over!\n";
    }
};

#endif // GAME_H