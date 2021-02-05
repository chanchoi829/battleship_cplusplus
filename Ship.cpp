#include "Ship.h"
#include <iostream>
#include <ncurses.h>

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
    wprintw(stdscr, "Computer's %s (length %d):", name.c_str(), length);

    if (hp == 0)
        wprintw(stdscr, " sunk\n");
    else
        wprintw(stdscr, " afloat\n");
}