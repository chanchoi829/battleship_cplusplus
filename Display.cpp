#include "Display.h"
#include "Engine.h"
#include "Grid.h"
#include "Utility.h"
#include <chrono>
#include <iostream>
#include <mutex>
#include <ncurses.h>
#include <thread>

using namespace std;

void Display::draw(Arguments* args) {
    initscr();
    while (!args->computer_wins && !args->player_wins) {
        {
            lock_guard<mutex> lock_d(args->m);
            wmove(stdscr, 0, 0);
            draw_computer_grid();
            draw_player_grid();

            // Show which computer ships have sunk
            wprintw(stdscr, "\n");
            engine.get_computer_ships()[0]->get_status();
            engine.get_computer_ships()[1]->get_status();
            engine.get_computer_ships()[2]->get_status();
            engine.get_computer_ships()[3]->get_status();
            engine.get_computer_ships()[4]->get_status();

            wrefresh(stdscr);
        }
        this_thread::sleep_for(chrono::milliseconds(30));
    }
    endwin();

    if (args->computer_wins)
        cout << "You Lose";
    else
        cout << "You win";
}

// Draw computer's grid
void Display::draw_computer_grid() {
    wprintw(stdscr, "\n      Enemy Grid\n\n  ");

    // Print numbers
    for (int i = 1; i <= 9; ++i)
        wprintw(stdscr, "%d ", i);

    wprintw(stdscr, "10\n");

    // Print letters
    for (char i = 'A'; i <= 'J'; ++i) {
        wprintw(stdscr, "%c ", i);

        for (int j = 0; j < 10; ++j) {
            Entity e = engine.get_computer_grid().get_grid()[i - 'A'][j].first;
            shared_ptr<Ship> ship = engine.get_computer_grid().get_grid()[i - 'A'][j].second;
            char tmp;
            // Do not show ships' locations to the player
            switch (e) {
                case Entity::Missed:
                    tmp = 'o';
                    break;
                case Entity::Sea:
                    tmp = '.';
                    break;
                case Entity::Vessel:
                    if (ship->is_hit(i - 'A', j))
                        tmp = 'x';
                    else
                        tmp = '.';
                    break;
                case Entity::Null:
                    tmp = '?';
                    break;
            }
            wprintw(stdscr, "%c ", tmp);
        }

        wprintw(stdscr, "\n");
    }
}

// Draw player's grid
void Display::draw_player_grid() {
    wprintw(stdscr, "\n      Your Grid\n\n  ");

    // Print numbers
    for (int i = 1; i <= 9; ++i)
        wprintw(stdscr, "%d ", i);

    wprintw(stdscr, "10\n");

    // Print letters
    for (char i = 'A'; i <= 'J'; ++i) {
        wprintw(stdscr, "%c ", i);

        for (int j = 0; j < 10; ++j) {
            Entity e = engine.get_player_grid().get_grid()[i - 'A'][j].first;
            shared_ptr<Ship> ship = engine.get_player_grid().get_grid()[i - 'A'][j].second;

            char tmp;
            switch (e) {
                // Don't show computer's missed attacks
                case Entity::Missed:
                case Entity::Sea:
                    tmp = '.';
                    break;
                case Entity::Vessel:
                    if (ship->is_hit(i - 'A', j))
                        tmp = 'x';
                    else
                        tmp = ship->get_letter();
                    break;
                case Entity::Null:
                    tmp = '?';
                    break;
            }
            wprintw(stdscr, "%c ", tmp);
        }

        wprintw(stdscr, "\n");
    }
}
