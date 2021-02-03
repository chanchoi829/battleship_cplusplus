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
    easy = false;
    row_prev = -1;
    col_prev = -1;
}

Computer::Computer(bool easy_) {
    ships_alive = 5;
    easy = easy_;
    row_prev = -1;
    col_prev = -1;
}

// Simulate computer's turn
void Computer::turn() {
    while (true) {
        int row, col, point;

        // Easy mode
        if (easy || row_prev == -1) {
            point = rand() % 100;
            row = point / 10;
            col = point % 10;
        }
        // Hard mode
        else {
            // Attack a point that is near the saved point
            // Up
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
            else {
                point = rand() % 100;
                row = point / 10;
                col = point % 10;
            }
        }

        // Attack a point that has not been attacked
        if (player_grid[row][col] != 'o' && player_grid[row][col] != 'x') {
            cout << "Computer attacks " << string(1, (point / 10) + 'A') << (point % 10) + 1 << ". ";
            // Miss
            if (player_grid[row][col] == '.') {
                player_grid[row][col] = 'o';

                cout << "Missed!" << endl;
            }
            // Hit
            else {
                int which_ship;
                string ship;
                convert_char_to_ship(player_grid[row][col], ship, which_ship);

                engine.get_player_ships()[which_ship].inject_damage();

                // Ship has been sunk
                if (engine.get_player_ships()[which_ship].get_hp()) {
                    cout << "Hit! Your " << ship << " has been sunk!" << endl;
                    engine.get_player().sink_ship();
                    row_prev = -1;
                    col_prev = -1;
                }
                // Ship has not been sunk
                else {
                    cout << "Hit!" << endl;

                    // Save the point for the hard mode
                    row_prev = row;
                    col_prev = col;
                }

                // Mark the grid
                player_grid[row][col] = 'x';
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
        engine.get_computer_grid().modify_grid(position / 10, position % 10, ship[0]);

    // Set the ship's hp
    engine.push_computer_ship(new_ship);
}

void Computer::sink_ship() {
    --ships_alive;
}

// Convert a char to a ship name
void Computer::convert_char_to_ship(char ship_char, string& ship, int& which_ship) {
    if (ship_char == 'd') {
        which_ship = 0;
        ship = "Destroyer";
    }
    else if (ship_char == 's') {
        which_ship = 1;
        ship = "Submarine";
    }
    else if (ship_char == 'c') {
        which_ship = 2;
        ship = "Cruiser";
    }
    else if (ship_char == 'b') {
        which_ship = 3;
        ship = "Battleship";
    }
    else {
        which_ship = 4;
        ship = "Carrier";
    }
}