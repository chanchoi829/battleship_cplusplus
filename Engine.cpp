#include "Computer.h"
#include "Display.h"
#include "Engine.h"
#include "Grid.h"
#include "Player.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>

using namespace std;

Engine::Engine() {
    args = new Arguments;
    display = thread(Display::draw, args);
}

// Run the game
void Engine::run() {
    // Reset the game
    reset();

    while (true) {
        // Player's turn
        player.turn();
        if (player.get_ships_alive() == 0)
            break;

        // Computer's turn
        computer.turn();
        if (computer.get_ships_alive() == 0)
            break;
    }

    delete args;
    return;
}

// Reset grids
void Engine::reset() {
    // Intialize default grids
    computer_grid = Grid();
    player_grid = Grid();

    computer = Computer(false);
    player = Player();

    // Create computer's grid
    player.place_ship_random("Destroyer");
    player.place_ship_random("Submarine");
    player.place_ship_random("Cruiser");
    player.place_ship_random("Battleship");
    player.place_ship_random("Carrier");

    // Create player's grid
    computer.place_ship("Destroyer");
    computer.place_ship("Submarine");
    computer.place_ship("Cruiser");
    computer.place_ship("Battleship");
    computer.place_ship("Carrier");
}

void Engine::push_computer_ship(Ship ship) {
    lock_guard<mutex>(args->m);
    computer_ships.push_back(ship);
}

void Engine::push_player_ship(Ship ship) {
    player_ships.push_back(ship);
}

// For Singleton
Engine& Engine::get_instance() {
    static Engine the_game;
    return the_game;
}
