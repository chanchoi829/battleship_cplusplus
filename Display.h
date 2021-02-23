#ifndef DISPLAY_H
#define DISPLAY_H

#include <coroutine>
#include <thread>

class Display {
public:
    void draw();
    
private:
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
    /*task animate_computer_attacks();
    task animate_player_attacks();
    auto animate_computer_attacks_co();*/
    
    std::thread animation_thread;
};

#endif