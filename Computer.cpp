#include "Computer.h"
#include "Engine.h"
#include "Utility.h"
#include <iostream>
#include <string>
#include <vector>

#define player_grid Engine::get_instance().get_player_grid().get_grid()

using namespace std;

Computer::Computer() {
    ships_alive = 5;
    row_prev = -1;
    col_prev = -1;
}

// Simulate computer's turn
void Computer::turn() {
    while (true) {
        int row, col, point;

        // Attack a point that is near the saved point
            // Up
        if (row_prev != -1 && col_prev != -1) {
            if (row_prev - 1 >= 0 && player_grid[row_prev - 1][col_prev] != 'o' && player_grid[row_prev - 1][col_prev] != 'x') {
                row = row_prev - 1;
                col = col_prev;
                point = row * 10 + col;
            }
            // Down
            else if (row_prev + 1 <= 9 && player_grid[row_prev + 1][col_prev] != 'o' && player_grid[row_prev + 1][col_prev] != 'x') {
                row = row_prev + 1;
                col = col_prev;
                point = row * 10 + col;
            }
            // Left
            else if (col_prev - 1 >= 0 && player_grid[row_prev][col_prev - 1] != 'o' && player_grid[row_prev][col_prev - 1] != 'x') {
                row = row_prev;
                col = col_prev - 1;
                point = row * 10 + col;
            }
            // Right
            else if (col_prev + 1 >= 0 && player_grid[row_prev][col_prev + 1] != 'o' && player_grid[row_prev][col_prev + 1] != 'x') {
                row = row_prev;
                col = col_prev + 1;
                point = row * 10 + col;
            }
        }
        else {
            point = rand() % 100;
            row = point / 10;
            col = point % 10;
        }

        // Attack a point that has not been attacked
        if (player_grid[row][col] != 'o' && player_grid[row][col] != 'x') {
            // Miss
            if (player_grid[row][col] == '.')
                engine.get_player_grid().modify_grid(row, col, 'o');
            // Hit
            else {
                int which_ship;
                string ship;
                convert_char_to_ship(player_grid[row][col], ship, which_ship);

                engine.get_player_ships()[which_ship].inject_damage();

                // Ship has been sunk
                if (engine.get_player_ships()[which_ship].get_hp() == 0) {
                    engine.get_player().sink_ship();
                    row_prev = -1;
                    col_prev = -1;
                }
                // Ship has not been sunk
                else {
                    // Save the point for the hard mode
                    row_prev = row;
                    col_prev = col;
                }

                // Mark the grid
                engine.get_player_grid().modify_grid(row, col, 'x');
            }
            return;
        }
    }
}

// Place a ship on the computer's grid
void Computer::place_ship(const string& ship) {
    Ship new_ship(ship);

    // Direction: left, up, right, down
    vector<int> points, directions = { -1, -10, 1, 10 };;

    // Generate random positions until the ship fits
    while (!is_valid(engine.get_computer_grid().get_grid(), points, rand() % 100, directions[rand() % 4], new_ship.get_hp())) {}

    // Place the ship
    for (int position : points)
        engine.get_computer_grid().modify_grid(position / 10, position % 10, new_ship.get_letter());

    // Set the ship's hp
    engine.push_computer_ship(new_ship);
}

void Computer::sink_ship() {
    --ships_alive;
}
