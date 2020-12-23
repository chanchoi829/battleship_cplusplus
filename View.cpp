#include "View.h"
#include "Model.h"
#include <iostream>
#include <string>
#include <utility>

using namespace std;

// Draw
void View::draw_computer_board() {

}

void View::draw_player_board() {
    cout << "      Your Board\n\n  ";

    for (char i = '1'; i <= '9'; ++i) {
        cout << i << " ";
    }

    cout << "10" << endl;

    for (char i = 'A'; i <= 'J'; ++i) {
        cout << string(1, i) << " ";

        for (int j = 0; j < 10; ++j)
            cout << Model::get_instance().get_player_board()[i - 'A'][j] << " ";

        cout << endl << endl;
    }
}
