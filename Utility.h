#ifndef UTILITIES_H
#define UTILITIES_H

#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#define engine Engine::get_instance()

class Ship;

struct Arguments {
    std::mutex m;
    std::pair<int, int> computer_attack, player_attack;
    bool computer_wins, player_wins, recently_attacked;

};

enum Entity { Vessel, Missed, Sea, Null };

// Check if the given ship can fit
bool is_valid(const std::vector<std::vector<std::pair<Entity, std::shared_ptr<Ship>>>>& grid, std::vector<int>& positions, int point, int direction, int ship_length);

#endif
