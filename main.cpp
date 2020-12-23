#include "Game.h"
#include "Utility.h"
#include <iostream>
#include <exception>
#include <algorithm>

using namespace std;

void run();
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

void run() {
    while (true) {
        try {
            Game::get_instance().reset();

            if (!restart())
                return;
            }
            // If an Error is thrown, skip rest of the line.
        catch (Error& e) {
            cout << e.what() << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

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