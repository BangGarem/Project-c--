//========================= StatusEffect.h =========================

#ifndef STATUS_EFFECT_H
#define STATUS_EFFECT_H

#include <string>

enum class StatusType {
    Burn,
    Poison,
    Stun,
    Weak
};

struct StatusEffect {
    StatusType type;
    int duration;
    int value;

    std::string name() const {
        switch (type) {
            case StatusType::Burn:   return "Burn";
            case StatusType::Poison: return "Poison";
            case StatusType::Stun:   return "Stun";
            case StatusType::Weak:   return "Weak";
        }
        return "Unknown";
    }
};

#endif