#include "Player.h"
#include "Engine.h"
#include "Ship.h"
#include <algorithm>
#include <iostream>
#include <ncurses.h>

using namespace std;

Player::Player() {
    ships_alive = 5;
}

// Simulate player's turn
void Player::turn() {
    for (const shared_ptr<Ship>& p : engine.get_computer_ships())
        p->reset_recently_sunk();

    MEVENT event;
    int row, col;
    
    while (true) {
        // Check if it's a click
        if (wgetch(stdscr) == KEY_MOUSE && getmouse(&event) == OK)
        {
            // Convert mouse position to row and column
            row = event.y - 4;
            col = (event.x - 2) / 2;
        }
        else {
            continue;
        }

        // Check if row or column is out of range
        if (row < 0 || row > 9 || col < 0 || col > 9) {
            continue;
        }
        // Check if the point has been attacked already
        else if (computer_grid[row][col].e == Grid::Entity::Missed ||
            (computer_grid[row][col].e == Grid::Entity::Vessel &&
                computer_grid[row][col].ship->is_hit(row, col))) {
            continue;
        }
        else {
            break;
        }   
    }


    lock_guard<mutex> lock2(engine.get_info()->m);
    engine.get_info()->recently_attacked = true;

    // Miss
    if (computer_grid[row][col].e == Grid::Entity::Sea) {
        engine.get_computer_grid().modify_grid(row, col, Grid::Entity::Missed);
        engine.get_info()->player_attack.push(
            vector<pair<int, int>> (1, make_pair(row, col))
        );

        return;
    }

    // Increment the ship's damage taken
    computer_grid[row][col].ship->inject_damage(row, col);

    // Mark the point
    engine.get_computer_grid().modify_grid(row, col, Grid::Entity::Vessel);

    // When hp is 0, the ship sinks
    if (computer_grid[row][col].ship->get_hp() == 0) {
        engine.get_computer().sink_ship();
        engine.get_info()->player_attack.push(
            computer_grid[row][col].ship->get_points()
        );
        return;
    }

    engine.get_info()->player_attack.push(
        vector<pair<int, int>>(1, make_pair(row, col))
    );
}


void Player::place_ship_random(Ship::Ship_type s) {
    shared_ptr<Ship> new_ship = make_shared<Ship>(s);

    // Direction: left, up, right, down
    vector<int> points, directions = { -1, -10, 1, 10 };;

    // Generate random positions until the ship fits
    while (!engine.get_player_grid().is_valid(points, rand() % 100,
        directions[rand() % 4], new_ship->get_hp()))
    {
    }

    vector<pair<int, int>> converted;
    // Place the ship
    for (int point : points)
        converted.push_back(make_pair(point / 10, point % 10));

    engine.get_player_grid().place_ship(converted, new_ship);
    new_ship->assign_points(converted);

    // Set the ship's hp
    engine.push_player_ship(new_ship);
}

void Player::sink_ship() {
    --ships_alive;
}

int Player::get_ships_alive() {
    return ships_alive;
}