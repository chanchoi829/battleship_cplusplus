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
    // Draw default grids
    sea = cimg_library::CImg<unsigned char> ("sea.jpg");
    ship = cimg_library::CImg<unsigned char> ("ship.jpg");
    black = cimg_library::CImg<unsigned char> ("black.jpg");
}

void Display_::draw() {
    // Render
    while (!info->computer_wins && !info->player_wins) {
        {
            draw_grids();
            info->computer_disp->render(computer_grid_image);
            info->player_disp->render(player_grid_image);            
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
        
    }
 
    if (info->computer_wins) {
        cout << "You Lose";
    }
    else {
        cout << "You win";
    }
}

void Display_::draw_grids() {
    computer_grid_image.clear();
    player_grid_image.clear();

    for (int i = 0; i < 10; ++i) {
        CImg<unsigned char> row_temp_player, row_temp_computer;
        for (int j = 0; j < 10; ++j) {
            row_temp_computer.append(black, 'x');

            // Assign images accordingly
            if (engine.get_player_grid().get_grid()[i][j].e == Grid::Entity::Vessel) {
                row_temp_player.append(ship, 'x');
            }
            else {
                row_temp_player.append(sea, 'x');
            }
        }
        computer_grid_image.append(row_temp_computer, 'y');
        player_grid_image.append(row_temp_player, 'y');
    }
}

void Display_::create_display() {
    info->computer_disp = make_shared<CImgDisplay>(computer_grid_image, "Computer Grid");
    info->player_disp = make_shared<CImgDisplay>(player_grid_image, "Player Grid");
}