#include "Computer.h"
#include "Engine.h"
#include "Ship.h"
#include "Utility.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#define player_grid Engine::get_instance().get_player_grid().get_grid()
#define can_attack(r, c) (player_grid[r][c].first == Entity::Sea || (player_grid[r][c].first == Entity::Vessel && !player_grid[r][c].second->is_hit(r, c)))

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
            if (row_prev - 1 >= 0 && can_attack(row_prev - 1, col_prev)) {
                row = row_prev - 1;
                col = col_prev;
                point = row * 10 + col;
            }
            // Down
            else if (row_prev + 1 <= 9 && can_attack(row_prev + 1, col_prev)) {
                row = row_prev + 1;
                col = col_prev;
                point = row * 10 + col;
            }
            // Left
            else if (col_prev - 1 >= 0 && can_attack(row_prev, col_prev - 1)) {
                row = row_prev;
                col = col_prev - 1;
                point = row * 10 + col;
            }
            // Right
            else if (col_prev + 1 >= 0 && can_attack(row_prev, col_prev + 1)) {
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
        else {
            point = rand() % 100;
            row = point / 10;
            col = point % 10;
        }

        // Attack a point that has not been attacked
        if (can_attack(row, col)) {
            lock_guard<mutex> lock(engine.get_args()->m);
            engine.get_args()->computer_attack = make_pair(row, col);
            // Miss
            if (player_grid[row][col].first == Entity::Sea) {
                engine.get_player_grid().modify_grid(row, col, Entity::Missed);
            }
                
            // Hit
            else {
                player_grid[row][col].second->inject_damage(row, col);

                // Ship has been sunk
                if (player_grid[row][col].second->get_hp() == 0) {
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
                engine.get_player_grid().modify_grid(row, col, Entity::Vessel);
            }

            return;
        }
    }
}

// Place a ship on the computer's grid
void Computer::place_ship(const string& ship) {
    shared_ptr<Ship> new_ship = make_shared<Ship>(ship);

    // Direction: left, up, right, down
    vector<int> points, directions = { -1, -10, 1, 10 };;

    // Generate random positions until the ship fits
    while (!is_valid(engine.get_computer_grid().get_grid(), points, rand() % 100, directions[rand() % 4], new_ship->get_hp())) {}

    vector<pair<int, int>> converted;
    // Place the ship
    for (int point : points)
        converted.push_back(make_pair(point / 10, point % 10));

    engine.get_computer_grid().place_ship(converted, new_ship);
    new_ship->assign_points(converted);
    // Set the ship's hp
    engine.push_computer_ship(new_ship);
}

void Computer::sink_ship() {
    --ships_alive;
}
