// ========================= Item.h =========================
#ifndef ITEM_H
#define ITEM_H

#include <string>

enum class ItemType {
    Potion,
    EnergyPotion,
    Antidote
};

struct Item {
    ItemType type;
    std::string name;
    int value;
};

#endif