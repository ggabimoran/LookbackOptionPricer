#ifndef LOOKBACKOPTION_H
#define LOOKBACKOPTION_H

/**
 *Import relevant libraries
 */
#include <vector>
/**
 *namespace used for lookbackoption_app to avoid naming collisions
 */
namespace lookback {
	/**
	 *abstract class to model lookbackoption
	 *contains option parameters and virtual functions for theoretical price and payoff simulation
	 */
	class LookbackOption {
	protected:
		///Current date t
		double t; 
		///Maturity T
		double T; 
		///Stock price at time t
		double St; 
		///risk-free rate
		double r;
		///volatility of the underlying
		double sigma;
	public:
		/*
		 *Parameterized constructor
		 *
		 *@throws std::invalid_argument if t<T, t<0, St,r or sigma<=0
		 *@param t Current date t
		 *@param T Maturity T
		 *@param St Stock price at time t
		 *@param r risk-free rate
		 *@param sigma volatility of the underlying
		 *@param init enum for initialization specification
		 */
		LookbackOption(double t_,double T_,double St_,double r_,double sigma_);
		///Copy constructor
		LookbackOption(const LookbackOption& option);
		///Copy assignment operator
		LookbackOption& operator=(const LookbackOption& option);
		///Destructor (!virtual since inheritance will be made)
		virtual ~LookbackOption() {};

		///getters
		double get_t() const { return t; }
		double get_T() const { return T; }
		double get_St() const { return St; }
		double get_r() const { return r; }
		double get_sigma() const { return sigma; }

		/**
		 *Setters
		 *@return *this to chain member function calls
		 */
		LookbackOption& set_t(double t_) { t = t_; return *this; }
		LookbackOption& set_T(double T_) { T = T_; return *this; }
		LookbackOption& set_St(double St_) { St = St_; return *this; }
		LookbackOption& set_r(double r_) { r = r_; return *this; }
		LookbackOption& set_sigma(double sigma_) { sigma = sigma_; return *this; }

		///pure virtual const analytical price
		virtual double analytical_price() const = 0;
		/**
		 *pure virtual const payoff simulation
		 *@param normSimulation vector of standard normal simulations of size the spatial discretization
		 *@return payoff estimate at maturity T
		 */
		virtual double simulate_payoff(std::vector<double> normSimulation) const = 0;
		///pure virtual copy function to copy a lookbackcall or lookbackput from abstract class pointer
		virtual LookbackOption* copy() const = 0;
	};
}
#endif // !LOOKBACKOPTION_H

