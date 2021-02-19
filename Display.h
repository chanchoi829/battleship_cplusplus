#ifndef DISPLAY_H
#define DISPLAY_H

#include <coroutine>

class Display {
public:
    Display();
    void draw();
    
private:
    void draw_computer_grid();
    void draw_player_grid();
    void blink_control(int freq, int limit);

    int counter, temp_counter;
    bool blink;
};

#endif