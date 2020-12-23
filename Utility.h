#ifndef UTILITIES_H
#define UTILITIES_H
#include <exception>

/* Utility declarations, functions, and classes used by more than one module */

// a simple class for error exceptions that inherits from std::exception
class Error : public std::exception {
public:
	Error(const char* msg_) : msg(msg_) {}
    const char* what() const noexcept override
        {return msg;}
private:
	const char* msg;
};

/* add any of your own declarations here */

// specified helper function				


#endif
