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
    mousemask(ALL_MOUSE_EVENTS | BUTTON1_CLICKED, NULL);
    mouseinterval(0);
    keypad(stdscr, TRUE);

    //animation_thread = thread(&Display::animate_computer_attacks, this);

    while (!info->computer_wins && !info->player_wins) {
        {
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

    if (info->computer_wins) {
        cout << "You Lose";
    }
    else {
        cout << "You win";
    }
}

/*auto Display::switch_to_new_thread(thread& out) {
    struct awaitable {
        thread* p_out;
        bool await_ready() { return false; }
        void await_suspend(coroutine_handle<> h) {
            thread& out = *p_out;
            if (out.joinable())
                throw std::runtime_error("Output jthread parameter not empty");
            out = thread([h] { h.resume(); });

            for (const pair<int, int>& point : info->computer_attack.front()) {
                mvwprintw(stdscr, point.second * 2 + 2, point.first + 18, " ");
            }

            info->computer_attack.pop();
        }
        void await_resume() {}
    };

    return awaitable{&out};
}*/

// Draw computer's grid
void Display::draw_computer_grid() {
    mvwprintw(stdscr, 0, 0, "\n      Enemy Grid\n\n  ");

    // Print numbers
    for (int i = 1; i <= 9; ++i)
        mvwprintw(stdscr, 3, i + i, "%d", i);

    mvwprintw(stdscr, 3, 20, "10\n");

    // Print letters
    for (char i = 'A'; i <= 'J'; ++i) {
        mvwprintw(stdscr, i - 'A' + 4, 0, "%c", i);

        for (int j = 0; j < 10; ++j) {
            Grid::Entity e =
                engine.get_computer_grid().get_grid()[i - 'A'][j].e;
            shared_ptr<Ship> ship =
                engine.get_computer_grid().get_grid()[i - 'A'][j].ship;
            char tmp;
            // Do not show ships' locations to the player
            switch (e) {
                case Grid::Entity::Unknown:
                    tmp = '?';
                    break;
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
            }

            mvwprintw(stdscr, i - 'A' + 4, j + j + 2, "%c", tmp);
        }

        mvwprintw(stdscr, i - 'A' + 4, 21, "\n");
    }
}

// Draw player's grid
void Display::draw_player_grid() {
    mvwprintw(stdscr, 14, 0, "\n      Your Grid\n\n  ");

    // Print numbers
    for (int i = 1; i <= 9; ++i)
        mvwprintw(stdscr, 17, i + i, "%d", i);

    mvwprintw(stdscr, 17, 20, "10\n");

    // Print letters
    for (char i = 'A'; i <= 'J'; ++i) {
        mvwprintw(stdscr, i - 'A' + 18, 0, "%c", i);

        for (int j = 0; j < 10; ++j) {
            Grid::Entity e =
                engine.get_player_grid().get_grid()[i - 'A'][j].e;
            shared_ptr<Ship> ship =
                engine.get_player_grid().get_grid()[i - 'A'][j].ship;

            char tmp;
            switch (e) {
                // Don't show computer's missed attacks
                case Grid::Entity::Unknown:
                    tmp = '?';
                    break;
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
            }

            mvwprintw(stdscr, i - 'A' + 18, j + j + 2, "%c", tmp);
        }

        mvwprintw(stdscr, i - 'A' + 18, 21, "\n");
    }
}

/*Display::task Display::animate_computer_attacks() {
    while (!info->computer_wins && !info->player_wins) {
        if (!info->computer_attack.empty()) {
            thread out;
            co_await switch_to_new_thread(out);
        }

        this_thread::sleep_for(chrono::milliseconds(30));
    }
}

Display::task Display::animate_player_attacks() {
}*/
