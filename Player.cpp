#include "Display.h"
#include "Engine.h"
#include "Player.h"
#include "Ship.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>
#include <ncurses.h>

using namespace std;

#define computer_grid engine.get_computer_grid().get_grid()

Player::Player() {
    ships_alive = 5;
}

// Simulate player's turn
void Player::turn() {
    while (true) {
        // Read in a point
        string point;
        read_point(point);

        for (const shared_ptr<Ship>& p : engine.get_computer_ships())
            p->reset_recently_sunk();

        // Convert to row and col
        int row = point[0] - 'a', col = point.length() == 3 ? 9 : point[1] - '1';

        // Check if the point has been attacked already
        if (computer_grid[row][col].first == Entity::Missed ||
            (computer_grid[row][col].first == Entity::Vessel &&
            computer_grid[row][col].second->is_hit(row, col)))
            continue;

        lock_guard<mutex> lock(engine.get_args()->m);
        engine.get_args()->player_start = true;
        engine.get_args()->player_attack = make_pair(row, col);

        // Miss
        if (computer_grid[row][col].first == Entity::Sea) {
            engine.get_computer_grid().modify_grid(row, col, Entity::Missed);
            return;
        }

        // Increment the ship's damage taken
        computer_grid[row][col].second->inject_damage(row, col);

        // When hp is 0, the ship sinks
        if (computer_grid[row][col].second->get_hp() == 0)
            engine.get_computer().sink_ship();

        // Mark the point
        engine.get_computer_grid().modify_grid(row, col, Entity::Vessel);

        return;
    }
}


void Player::place_ship_random(const std::string& ship) {
    shared_ptr<Ship> new_ship = make_shared<Ship>(ship);

    // Direction: left, up, right, down
    vector<int> points, directions = { -1, -10, 1, 10 };;

    // Generate random positions until the ship fits
    while (!is_valid(engine.get_player_grid().get_grid(), points, rand() % 100, directions[rand() % 4], new_ship->get_hp())) {}

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