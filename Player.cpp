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

    //lock_guard<mutex> lock2(engine.get_info()->m);
    MEVENT event;
    int row, col;
    
    while (true) {
        // Check if it's a double click
        if (wgetch(stdscr) == KEY_MOUSE && getmouse(&event) == OK)
        {
            // Convert mouse position to row and column
            row = event.x;
            col = event.y;

            wprintw(stdscr, "%d\n", row);
            wprintw(stdscr, "%d\n", col);
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

    engine.get_info()->recently_attacked = true;
    engine.get_info()->player_attack = make_pair(row, col);

    // Miss
    if (computer_grid[row][col].e == Grid::Entity::Sea) {
        engine.get_computer_grid().modify_grid(row, col, Grid::Entity::Missed);
        return;
    }

    // Increment the ship's damage taken
    computer_grid[row][col].ship->inject_damage(row, col);

    // When hp is 0, the ship sinks
    if (computer_grid[row][col].ship->get_hp() == 0)
        engine.get_computer().sink_ship();

    // Mark the point
    engine.get_computer_grid().modify_grid(row, col, Grid::Entity::Vessel);

    // Mark points for animation
    for (const pair<int, int>& p : computer_grid[row][col].ship->get_points())
        computer_grid[p.first][p.second].animation = true;
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

// Get user's input and check if it is valid
void Player::read_point(std::string& point) {
    while (true) {
        cin >> point;

        // Convert to lower case
        transform(point.begin(), point.end(), point.begin(),
            [](unsigned char c) { return tolower(c); });

        // Check the input
        if ((point.length() != 2 && point.length() != 3) || (point[0] < 'a' || point[0] > 'j'))
            continue;

        if (point.length() == 2 && (point[1] < '1' || point[1] > '9'))
            continue;

        if (point.length() == 3 && (point[1] != '1' || point[2] != '0'))
            continue;

        break;
    }
}

int Player::get_ships_alive() {
    return ships_alive;
}