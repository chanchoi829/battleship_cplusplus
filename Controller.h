/* Controller
This class is responsible for controlling the Model and View according to interactions
with the user.
*/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <functional>

class Controller {
public:
    Controller();
    void run();

private:

    bool restart();
    // Command maps
    std::map<std::string, 
        std::function<void
        (Controller*)>>command_map;
};

#endif