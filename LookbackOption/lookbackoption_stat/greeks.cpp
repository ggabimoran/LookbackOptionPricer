#include "greeks.h"
#include <cmath>
namespace lookback {
	double Greeks::alpha{ 0.01 };
	void Greeks::set_derivative_approx_params(double& divider, LookbackOption* payoffupper, LookbackOption* payofflower, LookbackOption* payoffmiddle,Greek_type type) {
		switch (type) {
		case Greek_type::delta:
			divider = payoffmiddle->get_St();
			payoffupper->set_St(divider * (1 + Greeks::alpha));
			payofflower->set_St(divider * (1 - Greeks::alpha));
			break;
		case Greek_type::gamma:
			divider = payoffmiddle->get_St();
			payoffupper->set_St(divider * (1 + Greeks::alpha));
			payofflower->set_St(divider * (1 - Greeks::alpha));
			break;
		case Greek_type::vega:
			divider = payoffmiddle->get_sigma();
			payoffupper->set_sigma(divider * (1 + Greeks::alpha));
			payofflower->set_sigma(divider * (1 - Greeks::alpha));
			break;
		case Greek_type::rho:
			divider = payoffmiddle->get_r();
			payoffupper->set_r(divider * (1 + Greeks::alpha));
			payofflower->set_r(divider * (1 - Greeks::alpha));
			break;
		case Greek_type::theta:
			divider = payoffmiddle->get_T() - payoffmiddle->get_t();
			payoffupper->set_t(payoffmiddle->get_t() * (1 + Greeks::alpha));
			payoffupper->set_T(payoffmiddle->get_T() * (1 + Greeks::alpha));
			break;
		}
	}
	/**copies option three times for upper,lower and middle value in derivative approximation
	 *all three are used for gamma : approximation of a second order derivative
	 *upper and lower are used for all others
	 *except theta: t can be null and the discounting must be done at different times so approximation done differently
	 */
	double Greeks::derivative_approx(const LookbackOption& option, const Matrix& normSimuls, Greek_type type) {
		double divider{ 0 }, greek;
		double Pt = exp(-option.get_r() * (option.get_T() - option.get_t()));
		LookbackOption *payoffupper{ option.copy() }, *payofflower{option.copy()}, *payoffmiddle{option.copy()};
		int M = normSimuls.get_M();
		std::vector<double> simulation{};
		set_derivative_approx_params(divider,payoffupper,payofflower,payoffmiddle,type);
		greek = 0;
		for (int i{ 0 }; i < M; ++i) {
			simulation = normSimuls(i);
			if (type == Greek_type::gamma) //second order derivative approx
				greek += Pt *(payoffupper->simulate_payoff(simulation) + payofflower->simulate_payoff(simulation) - 2 * payoffmiddle->simulate_payoff(simulation)) / (pow(Greeks::alpha * divider,2.0));
			else if (type == Greek_type::theta) // t may be equal to 0 and disounting must be done at different times so first order deriv approx is computed differently
				greek += (Pt * payoffmiddle->simulate_payoff(simulation) - pow(Pt,1+Greeks::alpha) * payoffupper->simulate_payoff(simulation)) / (divider * Greeks::alpha);
			else //first order derivative approx
				greek += Pt * (payoffupper->simulate_payoff(simulation) - payofflower->simulate_payoff(simulation)) / (2 * Greeks::alpha * divider);
		}
		greek /= M;
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