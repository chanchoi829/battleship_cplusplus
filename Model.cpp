#include "Model.h"
#include "Ship.h"
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

}

// Place a ship on the computer's board
void Model::place_computer_ship(const string& ship) {
    int ship_length;
    char ship_letter;

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

    // Direction: left, up, right, down
    vector<int> positions, directions = {-1, -10, 1, 10};;

    // Generate random positions until the ship fits
    while (!is_valid(positions, computer_board, rand() % 100, directions[rand() % 4], ship_length)) {}

    // Place the ship
    for (int position : positions)
        computer_board[position / 10][position % 10] = ship_letter;

    computer_ships.push_back(make_pair(0, false));
}

bool Model::is_valid(vector<int>& positions, const vector<vector<char>>& board, int position, int direction, int ship_length) {
    positions.clear();

    // Check if the ship fits
    bool ship_fits = true;

    ship_fits = true;
    for (int i = 0; i < ship_length; ++i) {
        int row = position / 10, col = position % 10;

        // Check if the position is in range and if the ship can fit
        if (position < 0 || position > 99 || computer_board[row][col] != '.') {
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
