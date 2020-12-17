#include "test_interface.h"

namespace lookback {
	void test_interface() {
		std::cout << "Testing execution\n";
		std::cout << "Matrix normSimuls{ 100,100 };\n";
		std::cout << "LookbackCall call{ 0,1,100,0.05,0.1 }\n";
		Matrix normSimuls{ 100,100 };
		LookbackCall call{ 0,1,100,0.05,0.1 };
		
		std::cout << "execute(0, 1, call, 100, 0.05, 0.1, 100, 100)\n";
		//std::cout << execute(0, 1, "call", 100, 0.05, 0.1, 100, 100) << '\n';
		std::cout << execute_convergence(0, 1, "call", 100, 0.05, 0.1, 100, "price") << '\n';
		std::cout << "Results written in lookbackoption_app directory OK\n";
	}
}