// ========================= Enemy.h =========================
#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character {
    int healCount;
    int turnCounter;

public:
    Enemy() {
        level = 1;
        maxHp = 150;
        hp = maxHp;
        baseDamage = 20;
        healCount = 2;
        turnCounter = 0;
    }

    void takeTurn(Character& player) override {
        turnCounter++;

        if (stunned) {
            std::cout << "Enemy turn skipped (stunned)\n";
            return;
        }

        if (hp < maxHp * 0.3f && healCount > 0) {
            healCount--;
            hp = std::min(hp + 30, maxHp);
            std::cout << "Enemy heals for 30 HP\n";
            return;
        }

        if (turnCounter % 3 == 0) {
            player.addStatus(StatusType::Poison, 4, 6);
            std::cout << "Enemy uses Poison skill\n";
        }

        int dmg = baseDamage * rng();
        player.receiveDamage(dmg);
        std::cout << "Enemy attacks for " << dmg << " damage\n";
    }
};

#endif