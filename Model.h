/*
Model class
*/

#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <vector>

class Ship;
class View;

class Model {

public:

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

    std::vector<std::vector<char>> computer_board, player_board;
    std::vector<std::shared_ptr<Ship>> computer_ships, player_ships;

};

#endif