#include <iostream>

#include "test_matrix.h"
#include "test_lookbackoption.h"
#include "test_greeks.h"
#include "test_interface.h"

int main() {
	try {
		//lookback::test_matrix();
		lookback::test_lookbackoption();
		//lookback::test_greeks();
		//lookback::test_interface();
	}
	catch (const std::exception &exception) {
		std::cerr << "Standard exception: " << exception.what() << '\n';
	}
	return 0;
}
