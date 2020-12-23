#include "Controller.h"
#include "Model.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

Controller::Controller() {

}

// Run the program by acccepting user commands
void Controller::run() {
    string command;
    Model::get_instance();
    while (true) {
        try {
            cout << "\nEnter command: ";
            cin >> command;
            // If the first word is "quit", check if View
            // is still open, and detach and delete view_ptr.
            // Then exit the while loop.

            if (command == "quit") {
                cout << "Done";
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