/*
Engine class
*/

#ifndef ENGINE_H
#define ENGINE_H

#include "Ship.h"
#include "Computer.h"
#include "Grid.h"
#include "Player.h"
#include <string>
#include <utility>
#include <vector>
#include <pthread.h>

struct Arguments;

class Engine {

public:
    void run();
    // Reset grids
    void reset();
    void push_computer_ship(Ship ship);
    void push_player_ship(Ship ship);

    // For Singleton
    static Engine& get_instance();

    // Getters
    std::vector<Ship>& get_computer_ships()
    {return computer_ships;}
    std::vector<Ship>& get_player_ships()
    {return player_ships;}
    Grid& get_computer_grid()
    {return computer_grid;}
    Grid& get_player_grid()
    {return player_grid;}
    Computer& get_computer() 
    {return computer;}
    Player& get_player()
    {return player;}
    pthread_t& get_c_thread()
    {return c_display;}
    pthread_t& get_p_thread()
    {return p_display;}
    Arguments* get_args()
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

    // Helper functions
    bool restart();

    Grid computer_grid, player_grid;
    Computer computer;
    Player player;

    Arguments* args;
    pthread_t c_display, p_display;

    std::vector<Ship> computer_ships, player_ships;
};

#endif
