#ifndef DISPLAY_H
#define DISPLAY_H

struct Arguments;

class Display {
public:
    static void draw(Arguments* args);
    static void draw_computer_grid();
    static void draw_player_grid();
private:

};

#endif