#ifndef GRID_H
#define GRID_H

#include "Ship.h"
#include <memory>
#include <utility>
#include <vector>

class Grid {

public:
    Grid();

    enum class Entity { Vessel, Missed, Sea, Null };

    struct Cell {
        Entity e = Entity::Sea;
        std::shared_ptr<Ship> ship;
        bool animation = false;
    };

    void place_ship(const std::vector<std::pair<int, int>>& points, std::shared_ptr<Ship> ship);
    void modify_grid(int row, int col, Entity e);

    // Check if the given ship can fit
    bool is_valid(std::vector<int>& positions, int point, int direction, int ship_length);
    std::vector<std::vector<Grid::Cell>>& get_grid();

private:
    std::vector<std::vector<Grid::Cell>> grid;
};

#endif
