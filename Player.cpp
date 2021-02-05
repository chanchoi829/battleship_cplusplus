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
        try {
            // Read in a point
            // cout << "\nExample: G5\nAttack a point: ";
            string point;
            read_point(point);

            // Convert to row and col
            int row = point[0] - 'a', col = point.length() == 3 ? 9 : point[1] - '1';

            // Check if the point has been attacked already
            if (computer_grid[row][col] == 'o' || computer_grid[row][col] == 'x')
                continue;

            // Miss
            if (computer_grid[row][col] == '.') {
                //cout << "Miss!" << endl;
                engine.get_computer_grid().modify_grid(row, col, 'o');

                return;
            }

            //cout << "Hit!" << endl;

            int which_ship;
            string ship;

            convert_char_to_ship(computer_grid[row][col], ship, which_ship);

            // Increment the ship's damage taken
            engine.get_computer_ships()[which_ship].inject_damage();

            // When hp is 0, the ship sinks
            if (engine.get_computer_ships()[which_ship].get_hp() == 0) {
                engine.get_computer().sink_ship();
                //cout << "Computer's " << ship << " sunk!" << endl;
            }

            // Mark the point
            engine.get_computer_grid().modify_grid(row, col, 'x');
            return;
        }
        // If an Error is thrown, skip rest of the line.
        catch (Error& e) {
            cout << e.what() << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Player::place_ship(const string& ship) {
    Ship new_ship(ship);
    while (true) {
        try {
            cout << "\nExample: G5\nPlace your " << ship << "(length " << new_ship.get_hp() << "): ";

            string point;
            read_point(point);

            cout << "\nExample: right\nEnter the direction(left/right/up/down): ";
            string direction;
            cin >> direction;

            transform(direction.begin(), direction.end(), direction.begin(),
                [](unsigned char c) { return tolower(c); });

            int direction_converted;

            // Convert direction to number
            if (direction == "left")
                direction_converted = -1;
            else if (direction == "up")
                direction_converted = -10;
            else if (direction == "right")
                direction_converted = 1;
            else if (direction == "down")
                direction_converted = 10;
            else
                throw Error("Enter a valid direction!\n");

            vector<int> points;

            // Convert point to a number (0 ~ 99)
            int position_converted = (point[0] - 'a') * 10 + (point.length() == 2 ? point[1] - '1' : 9);

            if (!is_valid(engine.get_player_grid().get_grid(), points, position_converted, direction_converted, new_ship.get_hp()))
                throw Error("Ship does not fit!\n");

            // Place the ship
            for (int pos : points)
                engine.get_player_grid().modify_grid(pos / 10, pos % 10, new_ship.get_letter());

            engine.push_player_ship(new_ship);
            break;
        }
        // If an Error is thrown, skip rest of the line.
        catch (Error& e) {
            cout << e.what() << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
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