#include "interface.h"

namespace lookback {
	std::vector<double> compute_greeks(const LookbackOption& option, const Matrix& normSimuls) {
		std::vector<double> greeks = std::vector<double>(5);
		greeks[0] = Greeks::delta(option, normSimuls);
		greeks[1] = Greeks::gamma(option, normSimuls);
		greeks[2] = Greeks::vega(option, normSimuls);
		greeks[3] = Greeks::rho(option, normSimuls);
		greeks[4] = Greeks::theta(option, normSimuls);
		return greeks;
	}
	Results execute(double t, double T, std::string type, double St, double r, double sigma, int M, int N) {
		clock_t tStart = clock();
		Results results{};
		int St_discretization = 10;
		double payoff_estimate;
		Matrix normSimuls{ M,N };
		LookbackOption* option;
		if (type.compare("call"))
			*option = LookbackCall(t, T, St, r, sigma);
		else
			*option = LookbackPut(t, T, St, r, sigma);
		results.greeks = compute_greeks(*option, normSimuls);
		results.P = option->analytical_price();
		results.deltas = std::vector<double>(St_discretization);
		results.prices = std::vector<double>(St_discretization);
		for (int k{ 0 }; k < St_discretization; ++k) {
			normSimuls = Matrix{ M,N };
			results.deltas[k] = Greeks::delta(*option,normSimuls);
			payoff_estimate = 0;
			for (int i{ 0 }; i < M; ++i) {
				payoff_estimate += option->simulate_payoff(normSimuls(i));
			}
			payoff_estimate /= M;
			results.prices[k] = payoff_estimate;
		}
		clock_t tEnd = clock();
		results.execution_time = static_cast<double>(tEnd - tStart)/CLOCKS_PER_SEC;
		return results;
	}
}