#ifndef DISPLAY_H
#define DISPLAY_H

#include <coroutine>

class Display {
public:
    Display();
    void draw();
    
private:
    struct Generator {
        struct Promise;

        // compiler looks for promise_type
        using promise_type = Promise;
        std::coroutine_handle<Promise> coro;
        Generator(std::coroutine_handle<Promise> h) : coro(h) {}

        ~Generator() {
            if (coro)
                coro.destroy();
        }
        // get current value of coroutine
        int value() {
            return coro.promise().val;
        }

        // advance coroutine past suspension
        bool next() {
            coro.resume();
            return !coro.done();
        }
        struct Promise {
            // current value of suspended coroutine
            int val;

            // called by compiler first thing to get coroutine result
            Generator get_return_object() {
                return Generator{ std::coroutine_handle<Promise>::from_promise(*this) };
            }
            // called by compiler first time co_yield occurs
            std::suspend_always initial_suspend() {
                return {};
            }

            // required for co_yield
            std::suspend_always yield_value(int x) {
                val = x;
                return {};
            }
            // called by compiler for coroutine without return
            std::suspend_never return_void() {
                return {};
            }

            // called by compiler last thing to await final result
            // coroutine cannot be resumed after this is called
            std::suspend_always final_suspend() {
                return {};
            }
        };

    };

    void draw_computer_grid();
    void draw_player_grid();
    void animate();
    void blink_control(int freq, int limit);

    int counter, temp_counter;
    bool blink;
};

#endif