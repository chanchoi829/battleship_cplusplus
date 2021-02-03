#include "Engine.h"
#include "Utility.h"
#include <iostream>
#include <exception>
#include <ctime>

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
