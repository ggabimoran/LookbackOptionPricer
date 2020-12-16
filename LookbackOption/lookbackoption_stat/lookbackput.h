#ifndef LOOKBACKPUT_H
#define LOOKBACKPUT_H

#include "lookbackoption.h"
/**
 *namespace used for lookbackoption_app to avoid naming collisions
 */
namespace lookback {
	/**
	 *class to model lookbackcall which inherits from lookbackoption
	 *contains option parameters and virtual functions for theoretical price and payoff simulation
	 */
	class LookbackPut : public LookbackOption {
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
		LookbackPut(double t, double T, double St, double r, double sigma) : LookbackOption(t, T, St, r, sigma) {};
		///Copy constructor
		LookbackPut(const LookbackPut& put) : LookbackOption(put) {};
		///Copy assignment operator
		LookbackPut& operator=(const LookbackPut& put) { LookbackOption::operator=(put); }
		///virtual destructor
		virtual ~LookbackPut() {};
		///virtual const analytical price
		virtual double analytical_price() const override;
		/**
		 *virtual const payoff simulation
		 *@param normSimulation vector of standard normal simulations of size the spatial discretization
		 *@return payoff estimate at maturity T
		 */
		virtual double simulate_payoff(std::vector<double> normSimulation) const override;
		///virtual copy function to copy a lookbackput from abstract class pointer
		virtual LookbackOption* copy() const override { return new LookbackPut(*this); }
	};
}

#endif // !LOOKBACKPUT_H
