#include "Display.h"
#include "Engine.h"
#include "Grid.h"
#include "Utility.h"
#include <iostream>
#include <pthread.h>

using namespace std;

// Draw computer's grid
void* Display::draw_computer_grid(void* args) {
    Arguments* p = (Arguments*)args;
    pthread_mutex_lock(&p->m);
    bool first_time = true;
    while (true) {
        // Wait until signaled
        p->print_computer = false;
        while (!p->print_computer) {
            if (!first_time)
                pthread_cond_signal(&p->cv_m);

            pthread_cond_wait(&p->cv_c, &p->m);
            first_time = false;
        }
            

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

    pthread_mutex_unlock(&p->m);

    return NULL;
}

// Draw player's grid
void* Display::draw_player_grid(void* args) {
    Arguments* p = (Arguments*)args;
    pthread_mutex_lock(&p->m);
    bool first_time = true;
    while (true) {
        // Wait until signaled
        p->print_player = false;
        while (!p->print_player) {
            if (!first_time)
                pthread_cond_signal(&p->cv_m);
            pthread_cond_wait(&p->cv_p, &p->m);
            first_time = false;
        }

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
    
    pthread_mutex_unlock(&p->m);

    return NULL;
}
