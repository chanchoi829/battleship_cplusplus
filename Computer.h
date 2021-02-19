#ifndef COMPUTER_H
#define COMPUTER_H

#include "Ship.h"
#include <string>

class Computer {
public:
    Computer();
    // Simulate computer's turn
    void turn();
    // Place computer's ship
    void place_ship(Ship::Ship_type s);
    void sink_ship();
    int get_ships_alive();

private:
    int ships_alive, row_prev, col_prev;
};

#endif