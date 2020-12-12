#include "greeks.h"
#include <cmath>
namespace lookback {
	double Greeks::alpha{ 0.01 };

	double Greeks::derivative_approx(LookbackOption& option, const Matrix& normSimuls, Greek_type type) {
		double divider, greek, payoffupper, payofflower, payoffmiddle;
		int M = normSimuls.get_M();
		std::vector<double> simulation{};
		greek = 0;
		for (int i{ 0 }; i < M; ++i) {
			simulation = normSimuls(i);
			switch (type) {
			case Greek_type::delta:
				divider = option.get_St();
				payoffupper = option.set_St(divider * (1 + Greeks::alpha)).simulate_payoff(simulation);
				payofflower = option.set_St(divider * (1 - Greeks::alpha)).simulate_payoff(simulation);
				option.set_St(divider);
				break;
			case Greek_type::gamma:
				divider = option.get_St();
				payoffupper = option.set_St(divider * (1 + Greeks::alpha)).simulate_payoff(simulation);
				payoffmiddle = option.set_St(divider).simulate_payoff(simulation);
				payofflower = option.set_St(divider * (1 - Greeks::alpha)).simulate_payoff(simulation);
				option.set_St(divider);
				break;
			case Greek_type::vega:
				divider = option.get_sigma();
				payoffupper = option.set_sigma(divider * (1 + Greeks::alpha)).simulate_payoff(simulation);
				payofflower = option.set_sigma(divider * (1 - Greeks::alpha)).simulate_payoff(simulation);
				option.set_sigma(divider);
				break;
			case Greek_type::rho:
				divider = option.get_r();
				payoffupper = option.set_r(divider * (1 + Greeks::alpha)).simulate_payoff(simulation);
				payofflower = option.set_r(divider * (1 - Greeks::alpha)).simulate_payoff(simulation);
				option.set_r(divider);
				break;
			case Greek_type::theta:
				divider = option.get_t();
				payoffupper = option.set_t(divider * (1 + Greeks::alpha)).simulate_payoff(simulation);
				payofflower = option.set_t(divider * (1 - Greeks::alpha)).simulate_payoff(simulation);
				option.set_t(divider);
				break;
			}
			if (type == Greek_type::gamma) //second order derivative approx
				greek += (payoffupper + payofflower - 2 * payoffmiddle) / (2 * Greeks::alpha * divider);
			else //first order derivative approx
				greek += (payoffupper - payofflower) / (2 * Greeks::alpha * divider);
		}
		return greek;
	}
	double Greeks::delta(LookbackOption& option, const Matrix& normSimuls) {
		return derivative_approx(option, normSimuls, Greek_type::delta);
	}
	double Greeks::gamma(LookbackOption& option, const Matrix& normSimuls) {
		return derivative_approx(option, normSimuls, Greek_type::gamma);
	}
	double Greeks::vega(LookbackOption& option, const Matrix& normSimuls) {
		return derivative_approx(option, normSimuls, Greek_type::vega);
	}
	double Greeks::rho(LookbackOption& option, const Matrix& normSimuls) {
		return derivative_approx(option, normSimuls, Greek_type::rho);
	}
	double Greeks::theta(LookbackOption& option, const Matrix& normSimuls) {
		return derivative_approx(option, normSimuls, Greek_type::theta);
	}
}