#include "test_greeks.h"
#include "matrix.h"
#include "lookbackcall.h"
#include "lookbackput.h"

namespace lookback {
	void test_greeks() {
		LookbackCall call{0,1,100,0.05,0.1};
		LookbackPut put{0,1,100,0.05,0.1};
		Matrix normSimuls(100, 100);

		std::cout << "Call delta: " << Greeks::delta(call, normSimuls) << '\n'; // should get approx 0.10 OK
		std::cout << "Call gamma: " << Greeks::gamma(call, normSimuls) << '\n'; // sould get approx 0 OK
		std::cout << "Call vega: " << Greeks::vega(call, normSimuls) << '\n';
		std::cout << "Call rho: " << Greeks::rho(call, normSimuls) << '\n';
		std::cout << "Call theta: " << Greeks::theta(call, normSimuls) << '\n';
		std::cout << '\n';
		std::cout << "Put delta: " << Greeks::delta(put, normSimuls) << '\n'; //should get approx 0.05 OK
		std::cout << "Put gamma: " << Greeks::gamma(put, normSimuls) << '\n'; //should get approx 0 OK
		std::cout << "Put vega: " << Greeks::vega(put, normSimuls) << '\n';
		std::cout << "Put rho: " << Greeks::rho(put, normSimuls) << '\n';
		std::cout << "Put theta: " << Greeks::theta(put, normSimuls) << '\n';
	}
}