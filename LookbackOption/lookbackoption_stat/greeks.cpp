#include "greeks.h"

namespace lookback {
	double Greeks::alpha{ 0.01 };

	double Greeks::derivative_approx(const LookbackOption& option, const Matrix& normSimuls, Greek_type type) {
		double divider, greek;
		LookbackOption *payoffupper;
		LookbackOption *payofflower;
		int M = normSimuls.get_M();
		std::vector<double> simulation{};
		switch (type) {
		case Greek_type::delta:
			*payoffupper = { option.get_t(),option.get_T(),option.get_St() * (1 + Greeks::alpha),option.get_r(),option.get_sigma() };
			*payoffupper = { option.get_t(),option.get_T(),option.get_St() * (1 - Greeks::alpha),option.get_r(),option.get_sigma() };
			divider = option.get_St();
			break;
		case Greek_type::gamma:
			//TODO
			divider = option.get_St();
			break;
		case Greek_type::vega:
			*payoffupper = { option.get_t(),option.get_T(),option.get_St(),option.get_r(),option.get_sigma() * (1 + Greeks::alpha) };
			*payoffupper = { option.get_t(),option.get_T(),option.get_St(),option.get_r(),option.get_sigma() * (1 - Greeks::alpha) };
			divider = option.get_sigma();
			break;
		case Greek_type::rho:
			*payoffupper = { option.get_t(),option.get_T(),option.get_St(),option.get_r() * (1 + Greeks::alpha),option.get_sigma() };
			*payoffupper = { option.get_t(),option.get_T(),option.get_St(),option.get_r() * (1 - Greeks::alpha),option.get_sigma() };
			divider = option.get_r();
			break;
		case Greek_type::theta:
			//TODO
			divider = option.get_T();
			break;
		}
		greek = 0;
		for (int i{ 0 }; i < M; ++i) {
			simulation = normSimuls(i);
			greek += payoffupper->simulate_payoff(simulation) - payofflower->simulate_payoff(simulation);
		}
		greek /= (2 * alpha * divider);
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