#ifndef GRID_H
#define GRID_H

#include "Utility.h"
#include <utility>
#include <vector>

class Ship;

class Grid {

public:
    Grid();

    void place_ship(const std::vector<std::pair<int, int>>& points, std::shared_ptr<Ship> ship);
    void modify_grid(int row, int col, Entity e);
    std::vector<std::vector<Cell>>& get_grid()
    {return grid;}

private:
    std::vector<std::vector<Cell>> grid;
};

#endif
