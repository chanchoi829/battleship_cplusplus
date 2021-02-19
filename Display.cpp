#include "Display.h"
#include "Engine.h"
#include "Grid.h"
#include "Ship.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <ncurses.h>
#include <thread>

using namespace std;


Display::Display() {
    blink = false;
    counter = 0;
    temp_counter = 0;
}

void Display::draw() {
    initscr();
    while (!info->computer_wins && !info->player_wins) {
        {
            lock_guard<mutex> lock_d(info->m);

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

            if (info->recently_attacked)
                blink_control(15, 60);
        }
        this_thread::sleep_for(chrono::milliseconds(30));
    }
    endwin();

    if (info->computer_wins)
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
            Grid::Entity e = engine.get_computer_grid().get_grid()[i - 'A'][j].e;
            shared_ptr<Ship> ship = engine.get_computer_grid().get_grid()[i - 'A'][j].ship;
            char tmp;
            // Do not show ships' locations to the player
            switch (e) {
                case Grid::Entity::Missed:
                    tmp = 'o';
                    break;
                case Grid::Entity::Sea:
                    tmp = '.';
                    break;
                case Grid::Entity::Vessel:
                    if (ship->is_hit(i - 'A', j))
                        tmp = 'x';
                    else
                        tmp = '.';
                    break;
                case Grid::Entity::Null:
                    tmp = '?';
                    break;
            }

            // Recently attacked spot blinks
            if (info->computer_attack.first != -1 && blink && info->player_attack.first == i - 'A' &&
                info->player_attack.second == j)
                tmp = ' ';

            if (info->computer_attack.first != -1 && blink && ship && ship->get_recently_sunk())
                tmp = ' ';

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
            Grid::Entity e = engine.get_player_grid().get_grid()[i - 'A'][j].e;
            shared_ptr<Ship> ship = engine.get_player_grid().get_grid()[i - 'A'][j].ship;

            char tmp;
            switch (e) {
                // Don't show computer's missed attacks
                case Grid::Entity::Missed:
                case Grid::Entity::Sea:
                    tmp = '.';
                    break;
                case Grid::Entity::Vessel:
                    if (ship->is_hit(i - 'A', j))
                        tmp = 'x';
                    else
                        tmp = ship->get_letter();
                    break;
                case Grid::Entity::Null:
                    tmp = '?';
                    break;
            }

            // Recently attacked spot blinks
            if (info->player_attack.first != -1 && blink && info->computer_attack.first == i - 'A' &&
                info->computer_attack.second == j)
                tmp = ' ';

            // Ship blinks when it recently has been attacked
            for (int i = 0; info->player_attack.first != -1 && blink && ship && i < ship->get_length(); ++i) {
                if (ship->get_points()[i].first == info->computer_attack.first && ship->get_points()[i].second == info->computer_attack.second) {
                    tmp = ' ';
                    break;
                }
            }

            wprintw(stdscr, "%c ", tmp);
        }

        wprintw(stdscr, "\n");
    }
}

void Display::blink_control(int freq, int limit) {
    if (counter == limit) {
        counter = 0;
        temp_counter = 0;
        blink = false;
        info->recently_attacked = false;
    }
    else {
        if (temp_counter < freq) {
            ++temp_counter;
            ++counter;
        }
        else {
            temp_counter = 0;
            blink = !blink;
        }
    }
}