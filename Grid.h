#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid {

public:
    Grid();

    void modify_grid(int row, int col, char c);

    std::vector<std::vector<char>>& get_grid()
    {return grid;}

private:
    std::vector<std::vector<char>> grid;
};

#endif
