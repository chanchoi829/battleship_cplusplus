#include "Utility.h"
#include <string>

using namespace std;

// Check if the given ship can fit
bool is_valid(const vector<vector<Cell>>& grid, vector<int>& positions, int point, int direction, int ship_length) {
    positions.clear();

    // Check if the ship fits
    bool ship_fits = true;

    for (int i = 0; i < ship_length; ++i) {
        int row = point / 10, col = point % 10;

        // Check if the point is in range and if the ship can fit
        if (point < 0 || point > 99 || (point % 10 == 0 && direction == -1) || (point % 10 == 9 && direction == 1)
            || grid[row][col].e != Entity::Sea) {
            ship_fits = false;
            break;
        }

        positions.push_back(point);
        point += direction;
    }

    return ship_fits;
}
