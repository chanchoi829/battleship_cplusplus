#include "Game.h"
#include "Utility.h"
#include <iostream>
#include <exception>
#include <algorithm>

using namespace std;

#define game Game::get_instance()

// Run the game
void run();
// Restart the battleship game
bool restart();

int main() {
	try {
        run();
    }
    // catch all exceptions not handled
    catch (exception& error) {
        cout << error.what() << endl;
    }
    catch (...) {
        cout << "Unknown exception caught" << endl;
    }
}

// Run the game
void run() {
    while (true) {
        try {

            // Reset the game
            game.reset();
            cout << "Game Start!" << endl;

            while (true) {
                // Print computer & player grids
                game.draw_computer_grid();
                cout << endl;

                // Player's turn
                game.player_turn();
                if (game.get_computer_sunk() == 5) {
                    cout << "You Win!" << endl;
                    break;
                }

                // Computer's turn
                game.computer_turn();
                if (game.get_player_sunk() == 5) {
                    cout << "You lose!" << endl;
                    break;
                }
            }

            if (!restart()) {
                cout << "Done" << endl;
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

// Restart the battleship game
bool restart() {
    string command;
    while (true) {
        try {
            cout << "Restart?\nType yes or no" << endl;

            cin >> command;

            transform(command.begin(), command.end(), command.begin(),
                [](unsigned char c){ return tolower(c); });

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
