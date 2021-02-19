#ifndef UTILITIES_H
#define UTILITIES_H

#include "Ship.h"
#include <memory>
#include <mutex>
#include <string>
#include <utility>

struct Information {
    std::mutex m;
    std::pair<int, int> computer_attack, player_attack;
    bool computer_wins, player_wins, recently_attacked;

};

enum class Entity { Vessel, Missed, Sea, Null };

struct Cell {
    Entity e = Entity::Sea;
    std::shared_ptr<Ship> ship;
    bool animation = false;
};

#endif
