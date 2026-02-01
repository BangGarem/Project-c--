// ========================= Player.h =========================
#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <fstream>
#include <limits> // for input validation
#include <iostream>

class Player : public Character {
    int exp;
    int expToNext;
    int ultimateCooldown; // new

public:
    Player() {
        level = 1;
        maxHp = 120;
        hp = maxHp;
        baseDamage = 18;
        energy = 0;
        exp = 0;
        expToNext = 100;
        ultimateCooldown = 0;
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
        // start-of-turn effects
        energy = std::min(energy + 20, 100);
        if (stunned) {
            std::cout << "Player is stunned! Turn skipped.\n";
            if (ultimateCooldown > 0) --ultimateCooldown;
            return;
        }

        // drop cooldown
        if (ultimateCooldown > 0) --ultimateCooldown;

        // action menu
        int choice = 0;
        while (true) {
            std::cout << "\n-- Your turn --\n";
            std::cout << "HP: " << hp << "/" << maxHp << "  Energy: " << energy << "  Ult CD: " << ultimateCooldown << "\n";
            std::cout << "1) Basic Attack\n";
            std::cout << "2) Skill (Burn) - cost 40\n";
            std::cout << "3) Ultimate - cost 100 (cooldown 3)\n";
            std::cout << "4) Save\n";
            std::cout << "Choose action: ";

            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, try again.\n";
                continue;
            }

            if (choice < 1 || choice > 4) {
                std::cout << "Invalid choice, try again.\n";
                continue;
            }
            break;
        }

        int dmg = 0;
        if (choice == 2) { // Skill: Burn
            if (energy < 40) {
                std::cout << "Not enough energy for Skill. Performing Basic Attack instead.\n";
                dmg = baseDamage;
                energy = std::min(energy + 20, 100);
            } else {
                energy -= 40;
                dmg = static_cast<int>(baseDamage * 1.5f);
                enemy.addStatus(StatusType::Burn, 3, 5);
                std::cout << "Player used Skill (Burn)!\n";
            }
        }
        else if (choice == 3) { // Ultimate
            if (energy < 100) {
                std::cout << "Not enough energy for Ultimate. Performing Basic Attack instead.\n";
                dmg = baseDamage;
                energy = std::min(energy + 20, 100);
            } else if (ultimateCooldown > 0) {
                std::cout << "Ultimate is on cooldown. Performing Basic Attack instead.\n";
                dmg = baseDamage;
                energy = std::min(energy + 20, 100);
            } else {
                energy -= 100;
                ultimateCooldown = 3;
                float crit = (rand() % 100 < 50) ? 2.0f : 1.5f;
                dmg = static_cast<int>(baseDamage * 4.0f * crit);
                std::cout << "Player used ULTIMATE! Massive damage!\n";
            }
        }
        else if (choice == 4) {
            save();
            return;
        }
        else { // Basic attack
            dmg = baseDamage;
            energy = std::min(energy + 20, 100);
            std::cout << "Player used Basic Attack.\n";
        }

        // apply multipliers and RNG
        dmg = static_cast<int>(dmg * adrenalineMultiplier() * rng() * damageModifier);
        enemy.receiveDamage(dmg);
        std::cout << "Dealt " << dmg << " damage.\n";
    }

    void save() {
        std::ofstream f("save.dat");
        f << level << " " << hp << " " << maxHp << " "
          << baseDamage << " " << energy << " "
          << exp << " " << expToNext << " " << ultimateCooldown;
    }

    void load() {
        std::ifstream f("save.dat");
        if (f)
            f >> level >> hp >> maxHp >> baseDamage >> energy >> exp >> expToNext >> ultimateCooldown;
    }
};

#endif