#include "greeks.h"
#include <cmath>
namespace lookback {
	double Greeks::alpha{ 0.01 };

	double Greeks::derivative_approx(const LookbackOption& option, const Matrix& normSimuls, Greek_type type) {
		double divider, greek;
		LookbackOption *payoffupper{ option.copy() }, *payofflower{option.copy()}, *payoffmiddle{option.copy()};
		int M = normSimuls.get_M();
		std::vector<double> simulation{};
		switch (type) {
	    case Greek_type::delta:
			divider = option.get_St();
			payoffupper->set_St(divider * (1 + Greeks::alpha));
			payofflower->set_St(divider * (1 - Greeks::alpha));
			break;
		case Greek_type::gamma:
			divider = option.get_St();
			payoffupper->set_St(divider * (1 + Greeks::alpha));
			payofflower->set_St(divider * (1 - Greeks::alpha));
			break;
		case Greek_type::vega:
			divider = option.get_sigma();
			payoffupper->set_sigma(divider * (1 + Greeks::alpha));
			payofflower->set_sigma(divider * (1 - Greeks::alpha));
			break;
		case Greek_type::rho:
			divider = option.get_r();
			payoffupper->set_r(divider * (1 + Greeks::alpha)).simulate_payoff(simulation);
			payofflower->set_r(divider * (1 - Greeks::alpha)).simulate_payoff(simulation);
			break;
		case Greek_type::theta:
			divider = option.get_t();
			payoffupper->set_t(divider * (1 + Greeks::alpha)).simulate_payoff(simulation);
			payofflower->set_t(divider * (1 - Greeks::alpha)).simulate_payoff(simulation);
			break;
		}
		greek = 0;
		for (int i{ 0 }; i < M; ++i) {
			simulation = normSimuls(i);
			if (type == Greek_type::gamma) //second order derivative approx
				greek += (payoffupper->simulate_payoff(simulation) + payofflower->simulate_payoff(simulation) - 2 * payoffmiddle->simulate_payoff(simulation)) / (pow(Greeks::alpha * divider,2.0));
			else //first order derivative approx
				greek += (payoffupper->simulate_payoff(simulation) - payofflower->simulate_payoff(simulation)) / (2 * Greeks::alpha * divider);
		}
		return greek;
	}
	double Greeks::delta(const LookbackOption& option, const Matrix& normSimuls) {
		return derivative_approx(option, normSimuls, Greek_type::delta);
	}
	double Greeks::gamma(const LookbackOption& option, const Matrix& normSimuls) {
		return derivative_approx(option, normSimuls, Greek_type::gamma);
	}
	double Greeks::vega(const LookbackOption& option, const Matrix& normSimuls) {
		return derivative_approx(option, normSimuls, Greek_type::vega);
	}
	double Greeks::rho(const LookbackOption& option, const Matrix& normSimuls) {
		return derivative_approx(option, normSimuls, Greek_type::rho);
	}
	double Greeks::theta(const LookbackOption& option, const Matrix& normSimuls) {
		return derivative_approx(option, normSimuls, Greek_type::theta);
	}
}