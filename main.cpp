#include "Game.h"
#include "Utility.h"
#include <iostream>
#include <exception>
#include <algorithm>
#include <ctime>

using namespace std;

#define game Game::get_instance()

// Run the game
void run();
// Check if the player wants to restart
bool restart();

int main() {
	try {
        // Set the seed for rand()
        srand(time(NULL));
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
            cout << "***************************\nGame Start!" << endl;

            while (true) {
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

// Check if the player wants to restart
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
