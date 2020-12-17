#include "test_greeks.h"
#include "matrix.h"
#include "lookbackcall.h"
#include "lookbackput.h"

namespace lookback {
	void test_greeks() {
		std::cout << "Testing greeks\n";
		std::cout << "LookbackCall call{0,1,100,0.05,0.1}\n";
		std::cout << "LookbackPut put{0,1,100,0.05,0.1}\n";
		std::cout << "Matrix normSimuls(1000, 1000);\n";
		LookbackCall call{0,1,100,0.05,0.1};
		LookbackPut put{0,1,100,0.05,0.1};
		Matrix normSimuls(1000, 1000);

		std::cout << "Call delta: " << "should get approx 0.10: " << Greeks::delta(call, normSimuls) << "  OK\n"; 
		std::cout << "Call gamma: " << "should get approx 0: " << Greeks::gamma(call, normSimuls) << "  OK\n"; 
		std::cout << "Call vega: " << "should get approx 70.17: " << Greeks::vega(call, normSimuls) << "   OK\n";
		std::cout << "Call rho: " << Greeks::rho(call, normSimuls) << '\n';
		std::cout << "Call theta: " << Greeks::theta(call, normSimuls) << '\n';
		std::cout << '\n';
		std::cout << "Put delta: " << "should get approx 0.05: " << Greeks::delta(put, normSimuls) << "  OK\n"; 
		std::cout << "Put gamma: " << "should get approx 0: " << Greeks::gamma(put, normSimuls) << "  OK\n"; 
		std::cout << "Put vega: " << "should get approx 79.97: " << Greeks::vega(put, normSimuls) << "   OK\n";
		std::cout << "Put rho: " << Greeks::rho(put, normSimuls) << '\n';
		std::cout << "Put theta: " << Greeks::theta(put, normSimuls) << '\n';
	}
}