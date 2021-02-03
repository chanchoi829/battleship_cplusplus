#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player();
    // Simulate player's turn
    void turn();

    // Place player's ship
    void place_ship(const std::string& ship);

    void sink_ship();

    // Get user's input and check if it is valid
    void read_point(std::string& point);

    int get_ships_alive()
    {return ships_alive;}

private:
    int ships_alive;
};

#endif
