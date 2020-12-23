#include "Game.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>
#include <stdlib.h>

using namespace std;

// Reset grids
void Game::reset() {
    row_prev = -1;
    col_prev = -1;

    string difficulty;
    while (true) {
        try {
            cout << "Example: hard\nChoose difficulty easy/hard: ";
            cin >> difficulty;
            cout << endl;

            transform(difficulty.begin(), difficulty.end(), difficulty.begin(),
                [](unsigned char c){ return tolower(c); });

            if (difficulty == "easy")
                easy = true;
            else if (difficulty == "hard")
                easy = false;
            else
                throw Error("Enter a valid difficulty!\n");

            break;
        }
        // If an Error is thrown, skip rest of the line.
        catch (Error& e) {
            cout << e.what() << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    computer_grid = vector<vector<char>> (10, vector<char>(10, '.'));
    player_grid = vector<vector<char>> (10, vector<char>(10, '.'));

    computer_ships.clear();
    player_ships.clear();

    // Create computer's grid
    place_computer_ship("Destroyer");
    place_computer_ship("Submarine");
    place_computer_ship("Cruiser");
    place_computer_ship("Battleship");
    place_computer_ship("Carrier");

    // Create player's grid
    place_player_ship("Destroyer");
    place_player_ship("Submarine");
    place_player_ship("Cruiser");
    place_player_ship("Battleship");
    place_player_ship("Carrier");

    computer_sunk = 0;
    player_sunk = 0;
}

// Simulate computer's turn
void Game::computer_turn() {
    while (true) {
        int row, col, position;

        // Easy mode
        if (easy || row_prev == -1) {
            position = rand() % 100;
            row = position / 10;
            col = position % 10;
        }
        // Hard mode
        else {
            if (row_prev - 1 >= 0 && player_grid[row_prev - 1][col_prev] != 'o' && player_grid[row_prev - 1][col_prev] != 'x') {
                row = row_prev - 1;
                col = col_prev;
                position = row * 10 + col;
            }
            else if (row_prev + 1 <= 9 && player_grid[row_prev + 1][col_prev] != 'o' && player_grid[row_prev + 1][col_prev] != 'x') {
                row = row_prev + 1;
                col = col_prev;
                position = row * 10 + col;
            }
            else if (col_prev - 1 >= 0 && player_grid[row_prev][col_prev - 1] != 'o' && player_grid[row_prev][col_prev - 1] != 'x') {
                row = row_prev;
                col = col_prev - 1;
                position = row * 10 + col;
            }
            else if (col_prev + 1 >= 0 && player_grid[row_prev][col_prev + 1] != 'o' && player_grid[row_prev][col_prev + 1] != 'x') {
                row = row_prev;
                col = col_prev + 1;
                position = row * 10 + col;
            }
            else {
                position = rand() % 100;
                row = position / 10;
                col = position % 10;
            }
        }

        if (player_grid[row][col] != 'o' && player_grid[row][col] != 'x') {
            cout << "Computer attacks " << string(1, (position / 10) + 'A') << (position % 10) + 1 << ". "; 
            if (player_grid[row][col] == '.') {
                player_grid[row][col] = 'o';

                cout <<  "Missed!" << endl;
            }
            else {
                int which_ship;
                string ship;
                convert_char_to_ship(player_grid[row][col], ship, which_ship);

                ++player_ships[which_ship].first;

                if (player_ships[which_ship].first == player_ships[which_ship].second) {
                    cout << "Hit! Your " << ship << " has been sunk!" << endl;
                    row_prev = -1;
                    col_prev = -1;
                }
                else {
                    cout << "Hit!" << endl;

                    // Save the point for the hard mode
                    row_prev = row;
                    col_prev = col;
                }

                player_grid[row][col] = 'x';
            }
            return;
        }
    }
}

// Simulate player's turn
void Game::player_turn() {
    while (true) {
        try {
            // Draw grids
            draw_computer_grid();
            cout << endl;
            draw_player_grid();

            cout << "***************************" << endl;
            cout << "Computer's Destroyer: " << (computer_ships[0].first == computer_ships[0].second ? "sunk" : "afloat") << endl;
            cout << "Computer's Submarine: " << (computer_ships[1].first == computer_ships[1].second ? "sunk" : "afloat") << endl;
            cout << "Computer's Cruiser: " << (computer_ships[2].first == computer_ships[2].second ? "sunk" : "afloat") << endl;
            cout << "Computer's Battleship: " << (computer_ships[3].first == computer_ships[3].second ? "sunk" : "afloat") << endl;
            cout << "Computer's Carrier: " << (computer_ships[4].first == computer_ships[4].second ? "sunk" : "afloat") << endl;
            cout << "\nExample: G5\nAttack a point: ";
            
            string position;
            read_position(position);
            int row = position[0] - 'a', col = position.length() == 3 ? 9 : position[1] - '1';

            if (computer_grid[row][col] == 'o' || computer_grid[row][col] == 'x')
                throw Error("Already attacked this point!\n");

            if (computer_grid[row][col] == '.') {
                cout << "Miss!" << endl;
                computer_grid[row][col] = 'o';
                return;
            }

            cout << "Hit!" << endl;

            int which_ship;
            string ship;

            convert_char_to_ship(computer_grid[row][col], ship, which_ship);

            ++computer_ships[which_ship].first;

            if (computer_ships[which_ship].first ==
                computer_ships[which_ship].second) {
                ++computer_sunk;
                cout << "Computer's " << ship << " sunk!" << endl;
            }

            computer_grid[row][col] = 'x';
            return;
        }
        // If an Error is thrown, skip rest of the line.
        catch (Error& e) {
            cout << e.what() << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Draw computer's grid
void Game::draw_computer_grid() {
   cout << "      Enemy Grid\n\n  ";

    for (char i = '1'; i <= '9'; ++i) {
        cout << i << " ";
    }

    cout << "10" << endl;

    for (char i = 'A'; i <= 'J'; ++i) {
        cout << string(1, i) << " ";


        for (int j = 0; j < 10; ++j) {
            char tmp = computer_grid[i - 'A'][j];
            if (tmp != '.' && tmp != 'o' && tmp != 'x')
                tmp = '.';
            cout << tmp << " ";
        }

        cout << endl << endl;
    } 
}

// Draw player's grid
void Game::draw_player_grid() {
    cout << "      Your Grid\n\n  ";

    for (char i = '1'; i <= '9'; ++i) {
        cout << i << " ";
    }

    cout << "10" << endl;

    for (char i = 'A'; i <= 'J'; ++i) {
        cout << string(1, i) << " ";

        for (int j = 0; j < 10; ++j) {
            char tmp = player_grid[i - 'A'][j];
            if (tmp == 'o')
                tmp = '.';
            cout << tmp << " ";
        }

        cout << endl << endl;
    }
}

// Place a ship on the computer's grid
void Game::place_computer_ship(const string& ship) {
    int ship_length;
    char ship_letter;

    check_ship_type(ship, ship_length, ship_letter);

    // Direction: left, up, right, down
    vector<int> positions, directions = {-1, -10, 1, 10};;

    // Generate random positions until the ship fits
    while (!is_valid(positions, computer_grid, rand() % 100, directions[rand() % 4], ship_length)) {}

    // Place the ship
    for (int position : positions)
        computer_grid[position / 10][position % 10] = ship_letter;

    computer_ships.push_back(make_pair(0, ship_length));
}

void Game::place_player_ship(const string& ship) {
    int ship_length;
    char ship_letter;

    check_ship_type(ship, ship_length, ship_letter);

    while (true) {
        try {
            draw_player_grid();
            cout << "\nExample: G5\nPlace your " << ship << "(length " << ship_length << "): ";
            
            string position;
            read_position(position);

            cout << "\nExample: right\nEnter the direction(left/right/up/down): ";
            string direction;
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

            if (!is_valid(positions, player_grid, position_converted, direction_converted, ship_length))
                throw Error("Ship does not fit!\n");

            // Place the ship
            for (int pos : positions)
                player_grid[pos / 10][pos % 10] = ship_letter;

            player_ships.push_back(make_pair(0, ship_length));
            break;
        }
        // If an Error is thrown, skip rest of the line.
        catch (Error& e) {
            cout << e.what() << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Game::check_ship_type(const string& ship, int& ship_length, char& ship_letter) {
    if (ship == "Destroyer") {
        ship_length = 2;
        ship_letter = 'd';
    }
    else if (ship == "Submarine") {
        ship_length = 3;
        ship_letter = 's';
    }
    else if (ship == "Cruiser"){ 
        ship_length = 3;
        ship_letter = 'c';
    }
    else if (ship == "Battleship") {
        ship_length = 4;
        ship_letter = 'b';
    }
    else {
        ship_length = 5;
        ship_letter = 'C';
    }  
}

bool Game::is_valid(vector<int>& positions, const vector<vector<char>>& grid, int position, int direction, int ship_length) {
    positions.clear();

    // Check if the ship fits
    bool ship_fits = true;

    ship_fits = true;
    for (int i = 0; i < ship_length; ++i) {
        int row = position / 10, col = position % 10;

        // Check if the position is in range and if the ship can fit
        if (position < 0 || position > 99 || (position % 10 == 0 && direction == -1) || (position % 10 == 9 && direction == 1)
            || grid[row][col] != '.') {
            ship_fits = false;
            break;
        }

        positions.push_back(position);
        position += direction;
    }

    return ship_fits;
}

// Get user's input and check if it is valid
void Game::read_position(std::string& position) {
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
}

// Convert a char to a ship name
void Game::convert_char_to_ship(char ship_char, string& ship, int& which_ship) {
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

// For Singleton
Game& Game::get_instance() {
    static Game the_game;
    return the_game;
}
