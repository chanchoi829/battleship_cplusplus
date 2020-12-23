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

    // disallow copy/move construction or assignment
    Model(Model& obj) = delete;
    Model(Model&& obj) = delete;
    Model& operator= (Model& obj) = delete;
    Model& operator= (Model&& obj) = delete;

private:
    // create the initial objects
    Model();
    ~Model(){}

    void place_ship(const std::string& ship);

    std::vector<std::vector<char>> computer_board, player_board;
    std::vector<std::pair<int, bool>> computer_ships, player_ships;

};

#endif