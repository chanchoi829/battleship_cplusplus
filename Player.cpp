#include "Display.h"
#include "Engine.h"
#include "Player.h"
#include "Ship.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>

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

        // Convert to row and col
        int row = point[0] - 'a', col = point.length() == 3 ? 9 : point[1] - '1';

        // Check if the point has been attacked already
        if (computer_grid[row][col] == 'o' || computer_grid[row][col] == 'x')
            continue;

        // Miss
        if (computer_grid[row][col] == '.') {
            engine.get_computer_grid().modify_grid(row, col, 'o');
            return;
        }

        int which_ship;
        string ship;

        convert_char_to_ship(computer_grid[row][col], ship, which_ship);

        // Increment the ship's damage taken
        engine.get_computer_ships()[which_ship].inject_damage();

        // When hp is 0, the ship sinks
        if (engine.get_computer_ships()[which_ship].get_hp() == 0)
            engine.get_computer().sink_ship();

        // Mark the point
        engine.get_computer_grid().modify_grid(row, col, 'x');
        return;
    }
}


void Player::place_ship_random(const std::string& ship) {
    Ship new_ship(ship);

    // Direction: left, up, right, down
    vector<int> points, directions = { -1, -10, 1, 10 };;

    // Generate random positions until the ship fits
    while (!is_valid(engine.get_player_grid().get_grid(), points, rand() % 100, directions[rand() % 4], new_ship.get_hp())) {}

    // Place the ship
    for (int position : points)
        engine.get_player_grid().modify_grid(position / 10, position % 10, new_ship.get_letter());

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