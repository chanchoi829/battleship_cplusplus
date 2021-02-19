#include "Engine.h"
#include "Computer.h"
#include "Display.h"
#include "Grid.h"
#include "Player.h"
#include "Ship.h"
#include <algorithm>

using namespace std;

Engine::Engine() {
    information = make_shared<Information>();
    information->computer_attack = make_pair(-1, -1);
    information->player_attack = make_pair(-1, -1);
    information->computer_wins = false;
    information->player_wins = false;
    information->recently_attacked = false;

    // Intialize default grids
    computer_grid_ = Grid();
    player_grid_ = Grid();
    computer = Computer();
    player = Player();
    display = Display();

    display_thread = thread(&Display::draw, display);
}

// Run the game
void Engine::run() {
    // Create computer's grid
    player.place_ship_random(Ship::Ship_type::Destroyer);
    player.place_ship_random(Ship::Ship_type::Submarine);
    player.place_ship_random(Ship::Ship_type::Cruiser);
    player.place_ship_random(Ship::Ship_type::Battleship);
    player.place_ship_random(Ship::Ship_type::Carrier);

    // Create player's grid
    computer.place_ship(Ship::Ship_type::Destroyer);
    computer.place_ship(Ship::Ship_type::Submarine);
    computer.place_ship(Ship::Ship_type::Cruiser);
    computer.place_ship(Ship::Ship_type::Battleship);
    computer.place_ship(Ship::Ship_type::Carrier);

    while (true) {
        // Player's turn
        player.turn();
        if (player.get_ships_alive() == 0) {
            information->computer_wins = true;
            break;
        }

        // Computer's turn
        computer.turn();
        if (computer.get_ships_alive() == 0) {
            information->player_wins = true;
            break;
        }
    }

    display_thread.join();
    return;
}

void Engine::push_computer_ship(shared_ptr<Ship> ship) {
    lock_guard<mutex> lock(information->m);
    computer_ships.push_back(ship);
}

void Engine::push_player_ship(shared_ptr<Ship> ship) {
    player_ships.push_back(ship);
}

// For Singleton
Engine& Engine::get_instance() {
    static Engine the_game;
    return the_game;
}

// Getters
vector<shared_ptr<Ship>>& Engine::get_computer_ships() {
    return computer_ships;
}

vector<shared_ptr<Ship>>& Engine::get_player_ships() {
    return player_ships;
}

Grid& Engine::get_computer_grid() {
    return computer_grid_;
}

Grid& Engine::get_player_grid() {
    return player_grid_;
}

Computer& Engine::get_computer() {
    return computer;
}

Player& Engine::get_player() {
    return player;
}
shared_ptr<Engine::Information> Engine::get_info() {
    return information;
}