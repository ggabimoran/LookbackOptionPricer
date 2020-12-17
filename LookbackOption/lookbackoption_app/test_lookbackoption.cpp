#include "test_lookbackoption.h"
#include "matrix.h"
#include <iostream>

namespace lookback {
	void test_lookbackoption() {
		std::cout << "Testing LookbackPut and LookbackCall constructors\n";
		std::cout << "LookbackCall call{ 0,0.5,100,0.05,0.1 }\n";
		std::cout << "LookbackPut put{ 0,1,50,0.05,0.1 }\n";
		LookbackCall call{ 0,0.5,100,0.05,0.1 };
		LookbackPut put{ 0,1,50,0.05,0.1 };
		std::cout << "LookbackPut and LookbackCall constructors OK\n";
		std::cout << "Testing LookbackPut and LookbackCall getters\n";
		std::cout << call.get_t() << ' ' << call.get_T() << ' ' << call.get_St() << ' ' << call.get_r() << ' ' << call.get_sigma() << '\n';
		std::cout << put.get_t() << ' ' << put.get_T() << ' ' << put.get_St() << ' ' << put.get_r() << ' ' << put.get_sigma() << '\n';
		std::cout << "LookbackPut and LookbackCall getters OK\n";

		std::cout << "Testing LookbackPut and LookbackCall setters\n";
		call.set_T(1);
		put.set_St(100);

		std::cout << call.get_t() << ' ' << call.get_T() << ' ' << call.get_St() << ' ' << call.get_r() << ' ' << call.get_sigma() << '\n';
		std::cout << put.get_t() << ' ' << put.get_T() << ' ' << put.get_St() << ' ' << put.get_r() << ' ' << put.get_sigma() << '\n';
		std::cout << "LookbackPut and LookbackCall setters OK\n";
		std::cout << "Testing LookbackCall copy\n";
		LookbackOption* pcall2{ call.copy() };
		pcall2->set_T(2);

		std::cout << call.get_t() << ' ' << call.get_T() << ' ' << call.get_St() << ' ' << call.get_r() << ' ' << call.get_sigma() << '\n';
		std::cout << pcall2->get_t() << ' ' << pcall2->get_T() << ' ' << pcall2->get_St() << ' ' << pcall2->get_r() << ' ' << pcall2->get_sigma() << '\n';
		std::cout << "LookbackCall copy OK\n";
		std::cout << "Testing LookbackCall copy constructor\n";
		LookbackCall call3{ call };

		std::cout << call.get_t() << ' ' << call.get_T() << ' ' << call.get_St() << ' ' << call.get_r() << ' ' << call.get_sigma() << '\n';
		std::cout << call3.get_t() << ' ' << call3.get_T() << ' ' << call3.get_St() << ' ' << call3.get_r() << ' ' << call3.get_sigma() << '\n';
		std::cout << "LookbackCall copy constructor OK\n";
		std::cout << '\n';
		std::cout << "Testing LookbackCall and LookbackPut analytical price\n";
		std::cout << "Call analytical price: " << "should get approx. 10.30 :" << call.analytical_price() << "   OK" << '\n';  
		std::cout << "Put analytical price: " << "should get approx 5.90 :"  <<put.analytical_price() << "   OK" << '\n';
		
		std::cout << '\n';
		std::cout << "Testing simulate_payoff\n";
		std::cout << "Matrix normSimuls(100, 100);\n";
		std::cout << '\n';
		Matrix normSimuls(10000, 100);
		std::vector<double> simulation{};
		double call_payoff_estimate{ 0 }, put_payoff_estimate{ 0 };
		double Pt = exp(-call.get_r() * (call.get_T() - call.get_t()));
		for (int i{ 0 }; i < 1000; ++i) {
			simulation = normSimuls(i);
			call_payoff_estimate += call.simulate_payoff(simulation);
			put_payoff_estimate += put.simulate_payoff(simulation);
		}
		call_payoff_estimate = call_payoff_estimate * Pt/1000;
		put_payoff_estimate = put_payoff_estimate * Pt/1000;
		std::cout << "Call payoff estimate for N=M=100: " << call_payoff_estimate << '\n';
		std::cout << "Put payoff estimate for N=M=100: " << put_payoff_estimate << '\n';
		std::cout << "Estimate payoff testing OK\n";
		std::cout << "Testing simulate payoff execution time\n";

		std::cout << '\n' << '\n';

		/*double execution_time;
		Matrix normSimuls100(100, 100);
		Matrix normSimuls1000(1000, 1000);
		clock_t tStart = clock();

		call_payoff_estimate = 0;
		Pt = exp(-call.get_r() * (call.get_T() - call.get_t()));
		for (int i{ 0 }; i < 100; ++i) {
			simulation = normSimuls100(i);
			call_payoff_estimate += Pt * call.simulate_payoff(simulation);
		}
		call_payoff_estimate /= 100;

		clock_t tEnd = clock();
		execution_time = static_cast<double>(tEnd - tStart) / CLOCKS_PER_SEC;
		std::cout << "Execution time to estimate call payoff for N=M=100: " << execution_time << 's' << '\n';

		std::cout << '\n' << '\n';

		tStart = clock();
		Pt = exp(-call.get_r() * (call.get_T() - call.get_t()));
		call_payoff_estimate = 0;
		for (int i{ 0 }; i < 1000; ++i) {
			simulation = normSimuls1000(i);
			call_payoff_estimate += Pt * call.simulate_payoff(simulation);
		}
		call_payoff_estimate /= 1000;

		tEnd = clock();
		execution_time = static_cast<double>(tEnd - tStart) / CLOCKS_PER_SEC;
		std::cout << "Execution time to estimate call payoff for N=M=1000: " << execution_time << 's' << '\n';*/
	}
}