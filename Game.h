/*
Game class
*/

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

class Game {

public:

    // Reset grids
    void reset();
    void draw_computer_grid();
    void draw_player_grid();
    // For Singleton
    static Game& get_instance();
    std::vector<std::vector<char>>& get_player_grid()
    {return player_grid;}

    // Disallow copy/move construction or assignment
    Game(Game& obj) = delete;
    Game(Game&& obj) = delete;
    Game& operator= (Game& obj) = delete;
    Game& operator= (Game&& obj) = delete;

private:
    // create the initial objects
    Game(){}
    ~Game(){}

    // Helper functions

    // Place computer's ship
    void place_computer_ship(const std::string& ship);

    // Place player's ship
    void place_player_ship(const std::string& ship);

    // Check the ship's type
    void check_ship_type(const std::string& ship, int& ship_length, char& ship_letter);

    // Check if the given ship can fit
    bool is_valid(std::vector<int>& positions, const std::vector<std::vector<char>>& grid,
        int position, int direction, int ship_length);

    // Boards
    std::vector<std::vector<char>> computer_grid, player_grid;

    // How many shots a ship has taken + sunk or not
    std::vector<std::pair<int, bool>> computer_ships, player_ships;
};

#endif