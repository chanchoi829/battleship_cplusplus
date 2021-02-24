#include "Display.h"

#define cimg_use_jpeg 1
#define cimg_use_png 1
#define cimg_use_tiff 1

#include "CImg.h"
#include "Engine.h"
#include "Grid.h"
#include "Ship.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

using namespace std;
using namespace cimg_library;

void Display_::draw() {
    CImg<unsigned char> image("sea.jpg");
    CImgDisplay main_disp(image,"Click a point");

    while (!info->computer_wins && !info->player_wins) {
        {
            
        }
        this_thread::sleep_for(chrono::milliseconds(30));
    }

    if (info->computer_wins) {
        cout << "You Lose";
    }
    else {
        cout << "You win";
    }
}

// Draw computer's grid
/*void Display::draw_computer_grid() {
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
}*/

// Draw player's grid
/*void Display::draw_player_grid() {
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
}*/
