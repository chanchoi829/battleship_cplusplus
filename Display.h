#ifndef DISPLAY_H
#define DISPLAY_H

#include <coroutine>
#include <thread>

class Display {
public:
    Display();
    void draw();
    
private:
    auto switch_to_new_thread(std::thread& out);

    struct task{
      struct promise_type {
        task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
      };
    };

    void draw_computer_grid();
    void draw_player_grid();
    void blink_control(int freq, int limit);

    int counter, temp_counter;
    bool blink;
};

#endif