#ifndef UTILITIES_H
#define UTILITIES_H

#include <exception>
#include <string>

// Error class
class Error : public std::exception {
public:
    Error(const char* msg_) : msg(msg_) {}
    const char* what() const noexcept override
        {return msg;}
private:
    const char* msg;
};

#endif
