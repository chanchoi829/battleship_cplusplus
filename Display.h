#ifndef DISPLAY_H
#define DISPLAY_H

#include <memory>

struct Arguments;

class Display {
public:
    static void draw(std::shared_ptr<Arguments> args);
    static void draw_computer_grid(std::shared_ptr<Arguments> args, bool blink);
    static void draw_player_grid(std::shared_ptr<Arguments> args, bool blink);
private:

};

#endif