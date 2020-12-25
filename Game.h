/*
Game class
*/

#ifndef GAME_H
#define GAME_H

#include <string>
#include <utility>
#include <vector>

class Game {

public:

    // Reset grids
    void reset();
    // Simulate computer's turn
    void computer_turn();
    // Simulate player's turn
    void player_turn();
    void draw_computer_grid();
    void draw_player_grid();
    // For Singleton
    static Game& get_instance();

    // Getters
    int get_computer_sunk()
    {return computer_sunk;}
    int get_player_sunk()
    {return player_sunk;}

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

    // Check the ship's type and assign values accordingly
    void check_ship_type(const std::string& ship, int& ship_length, char& ship_letter);

    // Check if the given ship can fit
    bool is_valid(std::vector<int>& positions, const std::vector<std::vector<char>>& grid,
        int position, int direction, int ship_length);

    // Get user's input and check if it is valid
    void read_position(std::string& position);

    // Convert a char to a ship name
    void convert_char_to_ship(char ship_char, std::string& ship, int& which_ship);

    // Boards
    std::vector<std::vector<char>> computer_grid, player_grid;

    // Number of ships sunk + ship HP
    std::vector<std::pair<int, int>> computer_ships, player_ships;

    // Keeps track of sunk ships. Saved points are for hard mode
    int computer_sunk, player_sunk, row_prev, col_prev;

    // Difficulty
    bool easy;
};

#endif
