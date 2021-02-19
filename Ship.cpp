#include "Ship.h"
#include <ncurses.h>

using namespace std;

Ship::Ship() {
    length = -1;
    hp = -1;
    letter = ' ';
    recently_sunk = false;
}

Ship::Ship(Ship::Ship_type s) {
    switch (s) {
        case Ship_type::Unknown:
            length = 0;
            hp = 0;
            letter = ' ';
            name = "Unknown";
        case Ship_type::Destroyer:
            length = 2;
            hp = 2;
            letter = 'd';
            hit = vector<bool>(2, false);
            name = "Destroyer";
            break;
        case Ship_type::Submarine:
            length = 3;
            hp = 3;
            letter = 's';
            hit = vector<bool>(3, false);
            name = "Submarine";
            break;
        case Ship_type::Cruiser:
            length = 3;
            hp = 3;
            letter = 'c';
            hit = vector<bool>(3, false);
            name = "Cruiser";
            break;
        case Ship_type::Battleship:
            length = 4;
            hp = 4;
            letter = 'b';
            hit = vector<bool>(4, false);
            name = "Battleship";
            break;
        case Ship_type::Carrier:
            length = 5;
            hp = 5;
            letter = 'C';
            hit = vector<bool>(5, false);
            name = "Carrier";
            break;
    }
}

void Ship::inject_damage(int row, int col) {
    --hp;

    if (hp == 0)
        recently_sunk = true;

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

void Ship::reset_recently_sunk() {
    recently_sunk = false;
}

// Getters
int Ship::get_letter() {
    return letter;
}

int Ship::get_hp() {
    return hp;
}

int Ship::get_length() {
    return length;
}

bool Ship::get_recently_sunk() {
    return recently_sunk;
}

vector<pair<int, int>>& Ship::get_points() {
    return points;
}