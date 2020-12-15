#include "test_interface.h"

namespace lookback {
	void test_interface() {
		Matrix normSimuls{ 100,100 };
		LookbackCall call{ 0,1,100,0.05,0.1 };
		std::vector<double> greeks = compute_greeks(call, normSimuls);
		for (int k{ 0 }; k < greeks.size(); ++k) {
			std::cout << greeks[k] << ' ';
		}
		std::cout << '\n' << '\n';

		Results results = execute(0, 1, "call", 100, 0.05, 0.1, 100, 100);
		std::cout << "results.greeks: ";
		for (int k{ 0 }; k < results.St_discretization; ++k) {
			std::cout << results.greeks[k] << ' ';
		}
		std::cout << '\n' << "results.prices: ";
		for (int k{ 0 }; k < results.St_discretization; ++k) {
			std::cout << results.prices[k] << ' ';
		}
		std::cout << '\n' << "results.deltas: ";
		for (int k{ 0 }; k < results.St_discretization; ++k) {
			std::cout << results.deltas[k] << ' ';
		}
		std::cout << '\n' << "Theoretical price : " << results.P << '\n';
		std::cout << '\n' << "Execution time : " << results.execution_time << '\n';

		std::cout << '\n' << '\n';

		std::vector<double> test = { 5,3,12,98,33,23,19 };
		double *test_convert = convert_std_vector(test);
		for (int k{ 0 }; k < test.size(); ++k)
			std::cout << test_convert[k] << ' ';
		std::cout << '\n';
	}
}