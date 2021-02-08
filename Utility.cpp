#include "Utility.h"
#include <string>

using namespace std;

// Check if the given ship can fit
bool is_valid(const vector<vector<pair<Entity, shared_ptr<Ship>>>>& grid, vector<int>& positions, int point, int direction, int ship_length) {
    positions.clear();

    // Check if the ship fits
    bool ship_fits = true;

    for (int i = 0; i < ship_length; ++i) {
        int row = point / 10, col = point % 10;

        // Check if the point is in range and if the ship can fit
        if (point < 0 || point > 99 || (point % 10 == 0 && direction == -1) || (point % 10 == 9 && direction == 1)
            || grid[row][col].first != Entity::Sea) {
            ship_fits = false;
            break;
        }

        positions.push_back(point);
        point += direction;
    }

    return ship_fits;
}


// Convert a char to a ship name
void convert_char_to_ship(char ship_char, string& ship, int& which_ship) {
    if (ship_char == 'd') {
        which_ship = 0;
        ship = "Destroyer";
    }
    else if (ship_char == 's') {
        which_ship = 1;
        ship = "Submarine";
    }
    else if (ship_char == 'c') {
        which_ship = 2;
        ship = "Cruiser";
    }
    else if (ship_char == 'b') {
        which_ship = 3;
        ship = "Battleship";
    }
    else {
        which_ship = 4;
        ship = "Carrier";
    }
}