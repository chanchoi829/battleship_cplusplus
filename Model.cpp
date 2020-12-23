#include "Model.h"
#include "Ship.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>
#include <stdlib.h>

using namespace std;

Model::Model() {

}


// Reset boards
void Model::reset() {
    computer_board = vector<vector<char>> (10, vector<char>(10, '.'));
    player_board = vector<vector<char>> (10, vector<char>(10, '.'));

    computer_ships.clear();
    player_ships.clear();

    // Create computer's board
    place_computer_ship("Destroyer");
    place_computer_ship("Submarine");
    place_computer_ship("Cruiser");
    place_computer_ship("Battleship");
    place_computer_ship("Carrier");

    // Create player's board
    place_player_ship("Destroyer");
    place_player_ship("Submarine");
    place_player_ship("Cruiser");
    place_player_ship("Battleship");
    place_player_ship("Carrier");
}

// Place a ship on the computer's board
void Model::place_computer_ship(const string& ship) {
    int ship_length;
    char ship_letter;

    check_ship_type(ship, ship_length, ship_letter);

    // Direction: left, up, right, down
    vector<int> positions, directions = {-1, -10, 1, 10};;

    // Generate random positions until the ship fits
    while (!is_valid(positions, computer_board, rand() % 100, directions[rand() % 4], ship_length)) {}

    // Place the ship
    for (int position : positions)
        computer_board[position / 10][position % 10] = ship_letter;

    computer_ships.push_back(make_pair(0, false));
}

void Model::place_player_ship(const string& ship) {
    int ship_length;
    char ship_letter;

    check_ship_type(ship, ship_length, ship_letter);

    while (true) {
        try {
            string position;

            cout << "\nExample: G5\nPlace your " << ship << "(length " << ship_length << "): ";
            cin >> position;

            transform(position.begin(), position.end(), position.begin(),
                [](unsigned char c){ return tolower(c); });

            // Check the input
            if ((position.length() != 2 && position.length() != 3) || (position[0] < 'a' || position[0] > 'j'))
                throw Error("Enter a valid answer!\n");

            if (position.length() == 2 && (position[1] < '1' || position[1] > '9'))
                throw Error("Enter a valid answer!\n");

            if (position.length() == 3 && (position[1] != '1' || position[2] != '0'))
                throw Error("Enter a valid answer!\n");

            string direction;

            cout << "\nExample: right\nEnter the direction(left/right/up/down): ";
            cin >> direction;
            
            transform(direction.begin(), direction.end(), direction.begin(),
                [](unsigned char c){ return tolower(c); });

            int direction_converted;

            if (direction == "left")
                direction_converted = -1;
            else if (direction == "up")
                direction_converted = -10;
            else if (direction == "right")
                direction_converted = 1;
            else if (direction == "down")
                direction_converted = 10;
            else
                throw Error("Enter a direction!\n");

            // Direction: left, up, right, down
            vector<int> positions;

            // Convert position to a number (0 ~ 99)
            int position_converted = (position[0] - 'a') * 10 + (position.length() == 2 ? position[1] - '1' : 9);

            if (!is_valid(positions, player_board, position_converted, direction_converted, ship_length))
                throw Error("Ship does not fit!\n");

            // Place the ship
            for (int pos : positions)
                player_board[pos / 10][pos % 10] = ship_letter;

            player_ships.push_back(make_pair(0, false));

            break;
        }
        // If an Error is thrown, skip rest of the line.
        catch (Error& e) {
            cout << e.what() << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Model::check_ship_type(const string& ship, int& ship_length, char& ship_letter) {
    if (ship == "Destroyer") {
        ship_length = 2;
        ship_letter = 'D';
    }
    else if (ship == "Submarine") {
        ship_length = 3;
        ship_letter = 'S';
    }
    else if (ship == "Cruiser"){ 
        ship_length = 3;
        ship_letter = 'c';
    }
    else if (ship == "Battleship") {
        ship_length = 4;
        ship_letter = 'B';
    }
    else {
        ship_length = 5;
        ship_letter = 'C';
    }  
}

bool Model::is_valid(vector<int>& positions, const vector<vector<char>>& board, int position, int direction, int ship_length) {
    positions.clear();

    // Check if the ship fits
    bool ship_fits = true;

    ship_fits = true;
    for (int i = 0; i < ship_length; ++i) {
        int row = position / 10, col = position % 10;

        // Check if the position is in range and if the ship can fit
        if (position < 0 || position > 99 || (position % 10 == 0 && direction == -1) || (position % 10 == 9 && direction == 1)
            || board[row][col] != '.') {
            ship_fits = false;
            break;
        }

        positions.push_back(position);
        position += direction;
    }

    return ship_fits;
}

// For Singleton
Model& Model::get_instance() {
    static Model the_model;
    return the_model;
}
