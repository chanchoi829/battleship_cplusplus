#include "Controller.h"
#include <iostream>
#include <exception>

using namespace std;

// The main function creates the Controller object, then tells it to run.

int main()
{
	try {
		// create the Controller and go
		Controller controller;
		controller.run();
	}
	// catch all exceptions not handled by Controller
	catch (std::exception& error) {
		cout << error.what() << endl;
	}
	catch (...) {
		cout << "Unknown exception caught" << endl;
	}

	return 0;
}
