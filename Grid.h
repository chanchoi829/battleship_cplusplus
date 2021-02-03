#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid {

public:
    Grid();
    // Reset the grid
    void clear();

    void modify_grid(int row, int col, char c);

    std::vector<std::vector<char>>& get_grid()
    {return grid;}

private:
    std::vector<std::vector<char>> grid;
};

#endif
