#include "Computer.h"
#include "Display.h"
#include "Engine.h"
#include "Grid.h"
#include "Player.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>
#include <pthread.h>

using namespace std;

typedef void* (*THREADFUNCPTR)(void*);

Engine::Engine() {
}

// Run the game
void Engine::run() {
    args = new Arguments;
    void* converted = args;
    pthread_create(&c_display, NULL, (THREADFUNCPTR) &Display::draw_computer_grid, converted);

    pthread_create(&p_display, NULL, (THREADFUNCPTR)&Display::draw_player_grid, converted);
    while (true) {
        try {
            // Reset the game
            reset();
            cout << "***************************\nGame Start!" << endl;

            while (true) {
                // Player's turn
                player.turn();
                if (player.get_ships_alive() == 0) {
                    cout << "You Win!" << endl;
                    break;
                }

                // Computer's turn
                computer.turn();
                if (computer.get_ships_alive() == 0) {
                    cout << "You lose!" << endl;
                    break;
                }
            }

            if (!restart()) {
                cout << "Done" << endl;
                delete args;
                return;
            }
        }
        // If an Error is thrown, skip rest of the line.
        catch (Error& e) {
            cout << e.what() << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Reset grids
void Engine::reset() {
    // Read in difficulty
    bool easy = false;
    string difficulty;
    while (true) {
        try {
            cout << "Example: hard\nChoose difficulty easy/hard: ";
            cin >> difficulty;
            cout << endl;

            // Convert to lower case
            transform(difficulty.begin(), difficulty.end(), difficulty.begin(),
                [](unsigned char c){ return tolower(c); });

            if (difficulty == "easy")
                easy = true;
            else if (difficulty == "hard")
                easy = false;
            else
                throw Error("Enter a valid difficulty!\n");

            break;
        }
        // If an Error is thrown, skip rest of the line.
        catch (Error& e) {
            cout << e.what() << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Intialize default grids
    computer_grid = Grid();
    player_grid = Grid();

    computer = Computer(easy);
    player = Player();

    // Create computer's grid
    player.place_ship("Destroyer");
    player.place_ship("Submarine");
    player.place_ship("Cruiser");
    player.place_ship("Battleship");
    player.place_ship("Carrier");

    // Create player's grid
    computer.place_ship("Destroyer");
    computer.place_ship("Submarine");
    computer.place_ship("Cruiser");
    computer.place_ship("Battleship");
    computer.place_ship("Carrier");
}

void Engine::push_computer_ship(Ship ship) {
    computer_ships.push_back(ship);
}

void Engine::push_player_ship(Ship ship) {
    player_ships.push_back(ship);
}

// Check if the player wants to restart
bool Engine::restart() {
    string command;
    while (true) {
        try {
            cout << "Restart?\nType yes or no" << endl;

            cin >> command;

            // Conver to lower case
            transform(command.begin(), command.end(), command.begin(),
                [](unsigned char c) { return tolower(c); });

            if (command == "yes")
                return true;
            else if (command == "no")
                return false;
            else
                throw Error("Invalid answer!\n");
        }
        // If an Error is thrown, skip rest of the line.
        catch (Error& e) {
            cout << e.what() << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// For Singleton
Engine& Engine::get_instance() {
    static Engine the_game;
    return the_game;
}
