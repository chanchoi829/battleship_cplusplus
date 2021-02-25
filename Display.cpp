#include "Display.h"

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

Display_::Display_() {
    // Load images
    sea_img = CImg<unsigned char> ("sea.jpg");
    ship_img = CImg<unsigned char> ("ship.jpg");
    black_img = CImg<unsigned char> ("black.jpg");
    red_img = CImg<unsigned char> ("red.jpg");
}

void Display_::draw() {
    // Render
    while (!info->computer_wins && !info->player_wins) {
        draw_grids();
        info->computer_disp->display(computer_grid_img);
        info->player_disp->display(player_grid_img);            
        this_thread::sleep_for(chrono::milliseconds(50));
    }
 
    if (info->computer_wins) {
        cout << "You Lose";
    }
    else {
        cout << "You win";
    }
}

void Display_::draw_grids() {
    CImg<unsigned char> computer_grid_temp, player_grid_temp;
    for (int i = 0; i < 10; ++i) {
        CImg<unsigned char> row_temp_player, row_temp_computer;
        for (int j = 0; j < 10; ++j) {

            // Assign images for computer's grid accordingly
            Grid::Entity point = engine.get_computer_grid().get_grid()[i][j].e;
            shared_ptr<Ship> ship = engine.get_computer_grid().get_grid()[i][j].ship;

            switch (point) {
                case Grid::Entity::Unknown:
                case Grid::Entity::Sea:
                    row_temp_computer.append(black_img, 'x');
                    break;
                case Grid::Entity::Missed:
                    row_temp_computer.append(sea_img, 'x');
                    break;
                case Grid::Entity::Vessel:
                    if (ship->is_hit(i, j)) {
                        row_temp_computer.append(red_img, 'x');
                    }
                    else {
                        row_temp_computer.append(black_img, 'x');
                    }
                    break;
            }

            // Assign images for player's grid accordingly
            point = engine.get_player_grid().get_grid()[i][j].e;
            ship = engine.get_player_grid().get_grid()[i][j].ship;

            switch (point) {
                case Grid::Entity::Unknown:
                case Grid::Entity::Sea:
                case Grid::Entity::Missed:
                    row_temp_player.append(sea_img, 'x');
                    break;
                case Grid::Entity::Vessel:
                    if (ship->is_hit(i, j)) {
                        row_temp_player.append(red_img, 'x');
                    }
                    else {
                        row_temp_player.append(ship_img, 'x');
                    }
                    break;
            }
        }

        computer_grid_temp.append(row_temp_computer, 'y');
        player_grid_temp.append(row_temp_player, 'y');
    }

    computer_grid_img = move(computer_grid_temp);
    player_grid_img = move(player_grid_temp);
}

void Display_::create_display() {
    info->computer_disp = make_shared<CImgDisplay>(computer_grid_img, "Computer Grid");
    info->player_disp = make_shared<CImgDisplay>(player_grid_img, "Player Grid");
}
