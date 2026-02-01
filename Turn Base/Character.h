// ========================= Character.h =========================
#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include "StatusEffect.h"

inline float rng(float min = 0.8f, float max = 1.2f) {
    return min + (float)rand() / RAND_MAX * (max - min);
}

class Character {
protected:
    int level;
    int hp, maxHp;
    int baseDamage;
    int energy;
    bool stunned;
    float damageModifier;
    std::vector<StatusEffect> effects;

public:
    Character()
        : level(1), hp(100), maxHp(100),
          baseDamage(10), energy(0),
          stunned(false), damageModifier(1.0f) {}

    virtual ~Character() = default;
    virtual void takeTurn(Character& target) = 0;

    void applyStatusEffects() {
        stunned = false;
        damageModifier = 1.0f;

        for (auto& e : effects) {
            switch (e.type) {
                case StatusType::Burn:
                case StatusType::Poison:
                    hp -= e.value;
                    break;
                case StatusType::Stun:
                    stunned = true;
                    break;
                case StatusType::Weak:
                    damageModifier = 0.7f;
                    break;
            }
            e.duration--;
        }

        effects.erase(
            std::remove_if(effects.begin(), effects.end(),
                [](const StatusEffect& e){ return e.duration <= 0; }),
            effects.end()
        );

        if (hp < 0) hp = 0;
    }

    void addStatus(StatusType t, int d, int v) {
        effects.push_back({t, d, v});
    }

    void receiveDamage(int dmg) {
        hp -= dmg;
        if (hp < 0) hp = 0;
    }

    bool isAlive() const { return hp > 0; }
    bool isStunned() const { return stunned; }

    int getHP() const { return hp; }
    int getMaxHP() const { return maxHp; }
    int getEnergy() const { return energy; }
    int getLevel() const { return level; }
};

#endif