// ========================= Player.h =========================
#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <fstream>

class Player : public Character {
    int exp;
    int expToNext;

public:
    Player() {
        level = 1;
        maxHp = 120;
        hp = maxHp;
        baseDamage = 18;
        energy = 0;
        exp = 0;
        expToNext = 100;
    }

    float adrenalineMultiplier() const {
        return (hp < maxHp * 0.3f) ? 1.5f : 1.0f;
    }

    void gainExp(int amount) {
        exp += amount;
        while (exp >= expToNext) {
            exp -= expToNext;
            level++;
            expToNext += 50;
            maxHp += 15;
            baseDamage += 4;
            hp = maxHp;
        }
    }

    void takeTurn(Character& enemy) override {
        energy = std::min(energy + 20, 100);
        if (stunned) return;

        int choice;
        std::cin >> choice;

        int dmg = 0;
        if (choice == 2 && energy >= 40) {
            energy -= 40;
            dmg = baseDamage * 1.5f;
            enemy.addStatus(StatusType::Burn, 3, 5);
        }
        else if (choice == 3 && energy >= 100) {
            energy -= 100;
            float crit = (rand() % 100 < 40) ? 2.0f : 1.2f;
            dmg = baseDamage * 3.0f * crit;
        }
        else if (choice == 4) {
            save();
            return;
        }
        else {
            dmg = baseDamage;
            energy = std::min(energy + 20, 100);
        }

        dmg = dmg * adrenalineMultiplier() * rng();
        enemy.receiveDamage(dmg);
    }

    void save() {
        std::ofstream f("save.dat");
        f << level << " " << hp << " " << maxHp << " "
          << baseDamage << " " << energy << " "
          << exp << " " << expToNext;
    }

    void load() {
        std::ifstream f("save.dat");
        if (f)
            f >> level >> hp >> maxHp >> baseDamage >> energy >> exp >> expToNext;
    }
};

#endif