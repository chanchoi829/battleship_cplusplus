#include "Engine.h"
#include "Utility.h"
#include <ctime>
#include <exception>
#include <iostream>

using namespace std;

int main() {
	try {
        // Set the seed for rand()
        srand(time(NULL));
        engine.run();
    }
    // catch all exceptions not handled
    catch (exception& error) {
        cout << error.what() << endl;
    }
    catch (...) {
        cout << "Unknown exception caught" << endl;
    }
}
