#ifndef GREEKS_H
#define GREEKS_H

#include "lookbackoption.h"
#include "matrix.h"
/**
 *namespace used for lookbackoption_app to avoid naming collisions
 */
namespace lookback {
	/**
	 *enum class to define the greek type
	 */
	enum class Greek_type {
		///Delta dP/dS
		delta,
		///Gamma d^2P/dS^2
		gamma,
		///Vega dP/dsigma
		vega,
		///Rho dP/dr
		rho,
		///Theta -dP/dtau
		theta
	};
	/**
	 *class used for greeks modelling
	 *all members are static
	 */
	class Greeks {
	private:
		///Derivative approximation precision parameter
		static double alpha; 
	public:
		/*
		 *Derivative approximation
		 *@param option abstract class pointer of option to compute greek
		 *@param normSimuls matrix of normal simulations
		 *@param type enum for greek type
		 *@return monte carlo approximation of derivative
		 */
		static double derivative_approx(std::vector<double> simulation, LookbackOption *payoffupper, LookbackOption *payofflower, LookbackOption *payoffmiddle, double divider, Greek_type type);
		///set derivative approximation parameters
		static void set_derivative_approx_params(double& divider, LookbackOption* payoffupper, LookbackOption* payofflower, LookbackOption* payoffmiddle, Greek_type type);
		///compute monte carlo estimation of derivative approximation
		static double monte_carlo_estimation(const LookbackOption& option, const Matrix& normSimuls, Greek_type type);
		///Monte carlo approximation of option delta for a given matrix of normal simulations
		static double delta(const LookbackOption& option, const Matrix& normSimuls);
		///Monte carlo approximation of option gamma for a given matrix of normal simulations
		static double gamma(const LookbackOption& option, const Matrix& normSimuls);
		///Monte carlo approximation of option delta for a given matrix of normal simulations
		static double vega(const LookbackOption& option, const Matrix& normSimuls);
		///Monte carlo approximation of option rho for a given matrix of normal simulations
		static double rho(const LookbackOption& option, const Matrix& normSimuls);
		///Monte carlo approximation of option theta for a given matrix of normal simulations
		static double theta(const LookbackOption& option, const Matrix& normSimuls);

		static double analytical_gamma() { return 0; }
		static double analytical_delta(const LookbackOption& option, std::string option_type);
	};
}

#endif // !GREEKS_H
