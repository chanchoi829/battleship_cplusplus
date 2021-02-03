#ifndef UTILITIES_H
#define UTILITIES_H

#include <exception>
#include <string>
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

// Check if the given ship can fit
bool is_valid(const std::vector<std::vector<char>>& grid, std::vector<int>& positions, int point, int direction, int ship_length);

// Convert a char to a ship name
void convert_char_to_ship(char ship_char, std::string& ship, int& which_ship);

#endif
