#include "Grid.h"
#include "Ship.h"
#include "Utility.h"
#include <mutex>

using namespace std;

Grid::Grid() {
    grid = vector<vector<Cell>> (10, vector<Cell>(10, Cell()));
}

void Grid::place_ship(const vector<pair<int, int>>& points, shared_ptr<Ship> ship) {
    for (const pair<int, int>& point : points) {
        grid[point.first][point.second].e = Entity::Vessel;
        grid[point.first][point.second].ship = ship;
    }
}

void Grid::modify_grid(int row, int col, Entity e) {
    if (e == Entity::Missed)
        grid[row][col].e = Entity::Missed;
}
