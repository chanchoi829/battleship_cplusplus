#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

class Computer {
public:
    Computer();
    // Simulate computer's turn
    void turn();
    // Place computer's ship
    void place_ship(const std::string& ship);
    void sink_ship();
    int get_ships_alive()
    {return ships_alive;}

private:
    void convert_char_to_ship(char ship_char, std::string& ship, int& which_ship);

    int ships_alive, row_prev, col_prev;
};

#endif