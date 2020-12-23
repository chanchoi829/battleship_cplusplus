#include "Utility.h"
#include <algorithm>
#include <iostream>

using namespace std;

// Get user's input and check if it is valid
void read_position(std::string& position) {
    cin >> position;

    transform(position.begin(), position.end(), position.begin(),
        [](unsigned char c){ return tolower(c); });

    // Check the input
    if ((position.length() != 2 && position.length() != 3) || (position[0] < 'a' || position[0] > 'j'))
        throw Error("Enter a valid answer!\n");

    if (position.length() == 2 && (position[1] < '1' || position[1] > '9'))
        throw Error("Enter a valid answer!\n");

    if (position.length() == 3 && (position[1] != '1' || position[2] != '0'))
        throw Error("Enter a valid answer!\n");
}
