/*
Engine class
*/

#ifndef ENGINE_H
#define ENGINE_H

#include "Computer.h"
#include "Display.h"
#include "Grid.h"
#include "Player.h"
#include <string>
#include <utility>
#include <vector>
#include <thread>
#include <memory>


struct Arguments;
class Ship;

class Engine {

public:
    void run();
    // Reset grids
    void push_computer_ship(std::shared_ptr<Ship> ship);
    void push_player_ship(std::shared_ptr<Ship> ship);

    // For Singleton
    static Engine& get_instance();

    // Getters
    std::vector<std::shared_ptr<Ship>>& get_computer_ships()
    {return computer_ships;}
    std::vector<std::shared_ptr<Ship>>& get_player_ships()
    {return player_ships;}
    Grid& get_computer_grid()
    {return computer_grid;}
    Grid& get_player_grid()
    {return player_grid;}
    Computer& get_computer() 
    {return computer;}
    Player& get_player()
    {return player;}
    std::shared_ptr<Arguments> get_args()
    {return args;}

    // Disallow copy/move construction or assignment
    Engine(Engine& obj) = delete;
    Engine(Engine&& obj) = delete;
    Engine& operator= (Engine& obj) = delete;
    Engine& operator= (Engine&& obj) = delete;

private:
    // create the initial objects
    Engine();
    ~Engine(){}

    Grid computer_grid, player_grid;
    Computer computer;
    Player player;
    Display display;

    std::shared_ptr<Arguments> args;
    std::thread display_thread;

    std::vector<std::shared_ptr<Ship>> computer_ships, player_ships;
};

#endif
