#include "Ship.h"
#include <iostream>

using namespace std;

Ship::Ship(const string& name_) {
    if (name_ == "Destroyer") {
        length = 2;
        hp = 2;
        letter = 'd';
    }
    else if (name_ == "Submarine"){
        length = 3;
        hp = 3;
        letter = 's';
    }
    else if (name_ == "Cruiser") {
        length = 3;
        hp = 3;
        letter = 'c';
    }
    else if (name_ == "Battleship") {
        length = 4;
        hp = 4;
        letter = 'b';
    }
    else {
        length = 5;
        hp = 5;
        letter = 'C';
    }

    name = name_;
}

void Ship::inject_damage() {
    --hp;
}

void Ship::get_status() {
    cout << "Computer's " << name << " (length " << length << "): ";

    if (hp == 0)
        cout << "sunk" << endl;
    else
        cout << "afloat" << endl;
}