#ifndef DISPLAY_H
#define DISPLAY_H

#define cimg_use_jpeg 1
#define cimg_use_png 1
#define cimg_use_tiff 1

#include "CImg.h"

class Display_
{
public:
    Display_();

    void draw();
    void draw_grids();
    void create_display();

private:
    cimg_library::CImg<unsigned char> computer_grid_img, player_grid_img, sea_img, ship_img, black_img, red_img;
};

#endif