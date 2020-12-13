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
		clock_t tStart = clock(); //start time

		Results results{}; //initialize variables
		int St_discretization = 10;
		double St_max = 2 * St;
		double St_min = 0;
		double payoff_estimate;
		Matrix normSimuls{ M,N };
		LookbackCall call{ t,T,St,r,sigma };
		LookbackPut put{ t,T,St,r,sigma };
		LookbackOption* option{ &call };
		if (type.compare("put")) option = &put;

		results.greeks = compute_greeks(*option, normSimuls); //compute option greeks
		results.P = option->analytical_price(); //compute option analytical price

		results.deltas = std::vector<double>(St_discretization); //compute deltas, prices for St discretization
		results.prices = std::vector<double>(St_discretization);
		for (int k{ 0 }; k < St_discretization; ++k) { // for each St value
			normSimuls = Matrix{ M,N }; // instantiate new matrix of normal simulations
			option->set_St(St_min + (St_max - St_min) * k / St_discretization); // set St
			results.deltas[k] = Greeks::delta(*option,normSimuls); //compute delta
			payoff_estimate = 0; //compute price estimate as empirical mean of M simulated payoffs
			for (int i{ 0 }; i < M; ++i) {
				payoff_estimate += option->simulate_payoff(normSimuls(i));
			}
			payoff_estimate /= M;
			results.prices[k] = payoff_estimate;
		}

		clock_t tEnd = clock(); //end time
		results.execution_time = static_cast<double>(tEnd - tStart)/CLOCKS_PER_SEC; //compute execution time
		return results; //return results struct
	}
}