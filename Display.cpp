#include "Display.h"
#include "Engine.h"
#include "Grid.h"
#include "Ship.h"
#include "Utility.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <ncurses.h>
#include <thread>

using namespace std;

void Display::draw(shared_ptr<Arguments> args) {
    initscr();
    bool blink = false;
    while (!args->computer_wins && !args->player_wins) {
        {
            lock_guard<mutex> lock_d(args->m);
            shared_ptr<Arguments> c = (args->computer_start) ? args : nullptr;
            shared_ptr<Arguments> p = (args->player_start) ? args : nullptr;

            wmove(stdscr, 0, 0);

            draw_computer_grid(c, blink);
            draw_player_grid(p, blink);

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
        blink = !blink;
    }
    endwin();

    if (args->computer_wins)
        cout << "You Lose";
    else
        cout << "You win";
}

// Draw computer's grid
void Display::draw_computer_grid(shared_ptr<Arguments> args, bool blink) {
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
void Display::draw_player_grid(shared_ptr<Arguments> args, bool blink) {
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

            // Recently attacked spot blinks
            if (args && blink && args->computer_attack.first == i - 'A' &&
                args->computer_attack.second == j)
                tmp = ' ';

            // Ship blinks when it recently has been attacked
            for (int i = 0; args && blink && ship && i < ship->get_length(); ++i) {
                if (ship->get_points()[i].first == i - 'A' && ship->get_points()[i].second == j) {
                    tmp = ' ';
                    break;
                }
            }

            wprintw(stdscr, "%c ", tmp);
        }

        wprintw(stdscr, "\n");
    }
}
