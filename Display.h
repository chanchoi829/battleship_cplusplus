#ifndef DISPLAY_H
#define DISPLAY_H

#include <pthread.h>

class Display {
public:
    static void* draw_computer_grid(void * args);
    static void* draw_player_grid(void * args);
private:

};

#endif