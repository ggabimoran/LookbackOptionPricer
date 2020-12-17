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
			divider = payoffmiddle->get_T();
			payoffupper->set_T(divider * (1 + Greeks::alpha));
			payofflower->set_T(divider * (1 - Greeks::alpha));
			break;
		}
	}
	/**copies option three times for upper,lower and middle value in derivative approximation
	 *all three are used for gamma : approximation of a second order derivative
	 *upper and lower are used for all others
	 *except theta: t can be null and the discounting must be done at different times so approximation done differently
	 */
	double Greeks::derivative_approx(std::vector<double> simulation, LookbackOption *payoffupper, LookbackOption *payofflower, LookbackOption *payoffmiddle, double divider, Greek_type type) {
		double Pt = exp(-payoffmiddle->get_r() * (payoffmiddle->get_T() - payoffmiddle->get_t()));
		if (type == Greek_type::gamma) //second order derivative approx
			return Pt *(payoffupper->simulate_payoff(simulation) + payofflower->simulate_payoff(simulation) - 2 * payoffmiddle->simulate_payoff(simulation)) / (pow(Greeks::alpha * divider,2.0));
		else if (type == Greek_type::theta) // disounting must be done at different times so first order deriv approx is computed differently
			return (pow(Pt,1-Greeks::alpha) * payofflower->simulate_payoff(simulation) - pow(Pt,1+Greeks::alpha) * payoffupper->simulate_payoff(simulation)) / (2 * divider * Greeks::alpha);
		else //first order derivative approx
			return Pt * (payoffupper->simulate_payoff(simulation) - payofflower->simulate_payoff(simulation)) / (2 * Greeks::alpha * divider);
	}
	double Greeks::monte_carlo_estimation(const LookbackOption& option, const Matrix& normSimuls, Greek_type type) {
		double divider{ 0 }, greek_estimate{ 0 };
		LookbackOption *payoffupper{ option.copy() }, *payofflower{ option.copy() }, *payoffmiddle{ option.copy() };
		set_derivative_approx_params(divider, payoffupper, payofflower, payoffmiddle, type);
		int M = normSimuls.get_M();
		std::vector<double> simulation{};
		for (int i{ 0 }; i < M; ++i) {
			simulation = normSimuls(i);
			greek_estimate += Greeks::derivative_approx(simulation, payoffupper, payofflower, payoffmiddle, divider, type);
		}
		greek_estimate /= M;
		return greek_estimate;
	}
	double Greeks::delta(const LookbackOption& option, const Matrix& normSimuls) {
		return monte_carlo_estimation(option, normSimuls, Greek_type::delta);
	}
	double Greeks::gamma(const LookbackOption& option, const Matrix& normSimuls) {
		return monte_carlo_estimation(option, normSimuls, Greek_type::gamma);
	}
	double Greeks::vega(const LookbackOption& option, const Matrix& normSimuls) {
		return monte_carlo_estimation(option, normSimuls, Greek_type::vega);
	}
	double Greeks::rho(const LookbackOption& option, const Matrix& normSimuls) {
		return monte_carlo_estimation(option, normSimuls, Greek_type::rho);
	}
	double Greeks::theta(const LookbackOption& option, const Matrix& normSimuls) {
		return monte_carlo_estimation(option, normSimuls, Greek_type::theta);
	}

	double Greeks::analytical_delta(const LookbackOption& option,std::string option_type) {
		auto normCDF{ [](double value) {return 0.5 * erfc(-value * sqrt(0.5)); } };
		double r1 = option.get_r() + pow(option.get_sigma(), 2) / 2;
		double tau = option.get_T() - option.get_t();
		double d = r1 * sqrt(tau) / option.get_sigma();
		double Pt = exp(-option.get_r() * tau);
		double C = pow(option.get_sigma(), 2) / (2 * option.get_r());
		double delta;
		if (option_type.compare("call") == 0) {
			double Nd1 = normCDF(d);
			double Nd2 = normCDF(-d);
			double Nd3 = normCDF(d - option.get_sigma() * sqrt(tau));
			delta = Nd1 - Pt * Nd3 - C * Nd2 + Pt * C * Nd3;
			return delta;
		}
		else {
			double Nd1 = normCDF(-d);
			double Nd2 = normCDF(d);
			double Nd3 = normCDF(-d + option.get_sigma() * sqrt(tau));
			delta = -Nd1 + Pt * Nd3 + C * Nd2 - Pt * C * Nd3;
			return delta;
		}
		return 0;
	}
}