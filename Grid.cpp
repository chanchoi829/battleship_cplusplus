#include "Grid.h"
#include "Engine.h"
#include "Ship.h"
#include "Utility.h"
#include <iostream>
#include <mutex>

using namespace std;

Grid::Grid() {
    grid = vector<vector<char>>(10, vector<char>(10, '.'));
}

void Grid::modify_grid(int row, int col, char c) {
    lock_guard<mutex> lock(engine.get_args()->m);
    grid[row][col] = c;
}
