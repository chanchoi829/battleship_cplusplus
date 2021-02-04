#ifndef UTILITIES_H
#define UTILITIES_H

#include <condition_variable>
#include <exception>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#define engine Engine::get_instance()

// Error class
class Error : public std::exception {
public:
    Error(const char* msg_) : msg(msg_) {}
    const char* what() const noexcept override
        {return msg;}
private:
    const char* msg;
};

struct Arguments {
    std::mutex m;
    std::condition_variable cv_c, cv_p, cv_m;
    bool print_computer = false, print_player = false;
};

// Check if the given ship can fit
bool is_valid(const std::vector<std::vector<char>>& grid, std::vector<int>& positions, int point, int direction, int ship_length);

// Convert a char to a ship name
void convert_char_to_ship(char ship_char, std::string& ship, int& which_ship);

#endif
