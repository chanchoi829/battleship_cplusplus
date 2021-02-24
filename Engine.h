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
#include <string>
#include <utility>
#include <vector>
#include <thread>
#include <memory>
#include <mutex>
#include <queue>

#define engine Engine::get_instance()
#define info Engine::get_instance().get_info()
#define computer_grid engine.get_computer_grid().get_grid()

typedef std::queue<std::vector<std::pair<int, int>>> Animation;

class Engine {

public:
    struct Information {
        std::mutex m;
        Animation computer_attack, player_attack;
        bool computer_wins, player_wins, recently_attacked;
    };

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
    std::shared_ptr<Engine::Information> get_info();

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
    Display_ display;

    std::shared_ptr<Information> information;
    std::thread display_thread;

    std::vector<std::shared_ptr<Ship>> computer_ships, player_ships;
};

#endif
