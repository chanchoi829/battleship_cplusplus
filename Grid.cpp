#include "Grid.h"
#include "Ship.h"
#include "Utility.h"
#include <mutex>

using namespace std;

Grid::Grid() {
    grid = vector<vector<pair<Entity, shared_ptr<Ship>>>>
        (10, vector<pair<Entity, shared_ptr<Ship>>>
            (10, make_pair(Entity::Sea, nullptr)));
}

void Grid::place_ship(const vector<pair<int, int>>& points, shared_ptr<Ship> ship) {
    for (const pair<int, int>& point : points) {
        grid[point.first][point.second].first = Entity::Vessel;
        grid[point.first][point.second].second = ship;
    }
}

void Grid::modify_grid(int row, int col, Entity e) {
    if (e == Entity::Missed)
        grid[row][col].first = Entity::Missed;
}
