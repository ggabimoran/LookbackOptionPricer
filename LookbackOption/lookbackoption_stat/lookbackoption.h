#ifndef LOOKBACKOPTION_H
#define LOOKBACKOPTION_H

#include <vector>

namespace lookback {

	class LookbackOption {
	private:
		double t; //current date
		double T; //maturity
		double S0;
		double r;
		double sigma;
	public:
		virtual double analytical_price() = 0;
		virtual double simulate_payoff(std::vector<double> normSimulation) = 0;
	};
}
#endif // !LOOKBACKOPTION_H

