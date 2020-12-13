#include <iostream>

#include "test_matrix.h"

int main() {
	try {
		lookback::test_matrix();
	}
	catch (const std::exception &exception) {
		std::cerr << "Standard exception: " << exception.what() << '\n';
	}
	return 0;
}
