#include "Grid.h"
#include "Ship.h"
#include "Utility.h"
#include <iostream>

using namespace std;

Grid::Grid() {
    grid = vector<vector<char>>(10, vector<char>(10, '.'));
}

void Grid::modify_grid(int row, int col, char c) {
    grid[row][col] = c;
}

// Reset the grid
void Grid::clear() {
    grid = vector<vector<char>>(10, vector<char>(10, '.'));
}
