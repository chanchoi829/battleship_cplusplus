#include "Display.h"
#include "Engine.h"
#include "Grid.h"
#include "Utility.h"
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

void Display::draw(Arguments* args) {
    while (true) {
        {
            unique_lock<mutex> lock_d(args->m);
            draw_computer_grid();
            draw_player_grid();
            lock_d.unlock();
        }
        this_thread::sleep_for(chrono::milliseconds(30));
    }
}

// Draw computer's grid
void Display::draw_computer_grid() {
    cout << endl;
    cout << "      Enemy Grid\n\n  ";

    // Print numbers
    for (char i = '1'; i <= '9'; ++i)
        cout << i << " ";

    cout << "10" << endl;

    // Print letters
    for (char i = 'A'; i <= 'J'; ++i) {
        cout << string(1, i) << " ";

        for (int j = 0; j < 10; ++j) {
            char tmp = engine.get_computer_grid().get_grid()[i - 'A'][j];
            // Do not show ships' locations to the player
            if (tmp != '.' && tmp != 'o' && tmp != 'x')
                tmp = '.';
            cout << tmp << " ";
        }

        cout << endl;
    }
}

// Draw player's grid
void Display::draw_player_grid() {
    cout << endl;
    cout << "      Your Grid\n\n  ";

    // Print numbers
    for (char i = '1'; i <= '9'; ++i)
        cout << i << " ";

    cout << "10" << endl;

    // Print letters
    for (char i = 'A'; i <= 'J'; ++i) {
        cout << string(1, i) << " ";

        for (int j = 0; j < 10; ++j) {
            char tmp = engine.get_player_grid().get_grid()[i - 'A'][j];
            // Don't show computer's missed attacks
            if (tmp == 'o')
                tmp = '.';
            cout << tmp << " ";
        }

        cout << endl;
    }
}
