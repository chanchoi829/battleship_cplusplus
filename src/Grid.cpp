#include "Grid.h"
#include "Ship.h"
#include <mutex>

using namespace std;

Grid::Grid()
{
    grid = vector<vector<Grid::Cell>>(10, vector<Grid::Cell>(10, Cell()));
}

// Place a ship in the given grid
void Grid::place_ship(const vector<pair<int, int>>& points, shared_ptr<Ship> ship)
{
    for (const pair<int, int>& point : points) {
        grid[point.first][point.second].e = Entity::Vessel;
        grid[point.first][point.second].ship = ship;
    }
}

// Modify the given point
void Grid::modify_grid(int row, int col, Entity e)
{
    if (e == Entity::Missed)
        grid[row][col].e = Entity::Missed;
}

// Check if the given ship can fit
bool Grid::is_valid(vector<int>& positions, int point, int direction, int ship_length)
{
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

// Getters
vector<vector<Grid::Cell>>& Grid::get_grid()
{
    return grid;
}