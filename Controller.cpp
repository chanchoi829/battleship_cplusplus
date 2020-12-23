#include "Controller.h"
#include "Model.h"
#include "Utility.h"
#include <cctype>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

Controller::Controller() {
    command_map = {
    };
}

// Run the program by acccepting user commands
void Controller::run() {
    string command;
    while (true) {
        try {
            
            Model::get_instance().reset();

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

bool Controller::restart() {
    string command;
    while (true) {
        try {
            cout << "Restart?\nType yes or no" << endl;

            cin >> command;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
