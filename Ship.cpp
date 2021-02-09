#include "Ship.h"
#include <iostream>
#include <ncurses.h>

using namespace std;

Ship::Ship() {
    length = -1;
    hp = -1;
    letter = ' ';
}

Ship::Ship(const std::string& name_) {
    if (name_ == "Destroyer") {
        length = 2;
        hp = 2;
        letter = 'd';
        hit = vector<bool>(2, false);
    }
    else if (name_ == "Submarine"){
        length = 3;
        hp = 3;
        letter = 's';
        hit = vector<bool>(3, false);
    }
    else if (name_ == "Cruiser") {
        length = 3;
        hp = 3;
        letter = 'c';
        hit = vector<bool>(3, false);
    }
    else if (name_ == "Battleship") {
        length = 4;
        hp = 4;
        letter = 'b';
        hit = vector<bool>(4, false);
    }
    else {
        length = 5;
        hp = 5;
        letter = 'C';
        hit = vector<bool>(5, false);
    }

    name = name_;
}

void Ship::inject_damage(int row, int col) {
    --hp;
    int offset = abs(row - points[0].first) + abs(col - points[0].second);
    hit[offset] = true;

}

void Ship::get_status() {
    wprintw(stdscr, "Computer's %s (length %d):", name.c_str(), length);
    if (hp == 0)
        wprintw(stdscr, " sunk\n");
    else
        wprintw(stdscr, " afloat\n");
}

void Ship::assign_points(vector<pair<int, int>>& points_) {
    points = move(points_);
}

bool Ship::is_hit(int row, int col) {
    int offset = abs(row - points[0].first) + abs(col - points[0].second);
    return hit[offset];
}