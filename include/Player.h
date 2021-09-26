#ifndef PLAYER_H
#define PLAYER_H

#include "Ship.h"
#include <string>

class Player {
public:
    Player();
    // Simulate player's turn
    void turn();

    void place_ship_random(Ship::Ship_type s);

    void sink_ship();

    int get_ships_alive();

private:
    int ships_alive;
};

#endif
