/*
Model class
*/

#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

class View;

class Model {

public:

    // Reset boards
    void reset();

    // For Singleton
    static Model& get_instance();
    std::vector<std::vector<char>>& get_player_board()
    {return player_board;}

    // Disallow copy/move construction or assignment
    Model(Model& obj) = delete;
    Model(Model&& obj) = delete;
    Model& operator= (Model& obj) = delete;
    Model& operator= (Model&& obj) = delete;

private:
    // create the initial objects
    Model();
    ~Model(){}

    // Helper functions

    // Place computer's ship
    void place_computer_ship(const std::string& ship);

    // Place player's ship
    void place_player_ship(const std::string& ship);

    // Check the ship's type
    void check_ship_type(const std::string& ship, int& ship_length, char& ship_letter);

    // Check if the given ship can fit
    bool is_valid(std::vector<int>& positions, const std::vector<std::vector<char>>& board,
        int position, int direction, int ship_length);

    // Boards
    std::vector<std::vector<char>> computer_board, player_board;

    // How many shots a ship has taken + sunk or not
    std::vector<std::pair<int, bool>> computer_ships, player_ships;

    std::shared_ptr<View> view_ptr;
};

#endif