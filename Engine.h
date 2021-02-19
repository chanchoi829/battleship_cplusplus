/*
Engine class
*/

#ifndef ENGINE_H
#define ENGINE_H

#include "Computer.h"
#include "Display.h"
#include "Grid.h"
#include "Player.h"
#include "Ship.h"
#include "Utility.h"
#include <string>
#include <utility>
#include <vector>
#include <thread>
#include <memory>

#define engine Engine::get_instance()
#define info Engine::get_instance().get_info()
#define computer_grid engine.get_computer_grid().get_grid()

class Engine {

public:
    void run();
    // Reset grids
    void push_computer_ship(std::shared_ptr<Ship> ship);
    void push_player_ship(std::shared_ptr<Ship> ship);

    // For Singleton
    static Engine& get_instance();

    // Getters
    std::vector<std::shared_ptr<Ship>>& get_computer_ships();
    std::vector<std::shared_ptr<Ship>>& get_player_ships();
    Grid& get_computer_grid();
    Grid& get_player_grid();
    Computer& get_computer();
    Player& get_player();
    std::shared_ptr<Information> get_info();

    // Disallow copy/move construction or assignment
    Engine(Engine& obj) = delete;
    Engine(Engine&& obj) = delete;
    Engine& operator= (Engine& obj) = delete;
    Engine& operator= (Engine&& obj) = delete;

private:
    // create the initial objects
    Engine();
    ~Engine(){}

    Grid computer_grid_, player_grid_;
    Computer computer;
    Player player;
    Display display;

    std::shared_ptr<Information> information;
    std::thread display_thread;

    std::vector<std::shared_ptr<Ship>> computer_ships, player_ships;
};

#endif
