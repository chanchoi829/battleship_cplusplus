#include "Model.h"
#include "Ship.h"

using namespace std;

Model::Model() {
    reset();
}


void Model::reset() {
    // Create computer's board
    computer_board = vector<vector<char>> (10, vector<char>('.', 10));
    player_board = vector<vector<char>> (10, vector<char>('.', 10));
}

// for Singleton
Model& Model::get_instance() {
    static Model the_model;
    return the_model;
}
