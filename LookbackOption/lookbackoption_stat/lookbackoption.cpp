#include "lookbackoption.h"

namespace lookback {
	LookbackOption::LookbackOption(double t_, double T_, double St_, double r_, double sigma_) 
		: t{ t_ }, T{ T_ }, St{ St_ }, r{ r_ }, sigma{ sigma_ }{
		if (t_ >= T_) throw std::invalid_argument("Lookback Option maturity T must be greater than current date t");
		if (t_ < 0) throw std::invalid_argument("Lookback Option current date t and maturity T must be positive");
		if (sigma_ <= 0) throw std::invalid_argument("Lookback Option volatility must be strictly positive");
		if (r <= 0) throw std::invalid_argument("Interest rate r must be positive");
		if (St_ <= 0) throw std::invalid_argument("Lookback Option intial price St must be strictly positive");
	}
	LookbackOption::LookbackOption(const LookbackOption& option)
		: t{ option.t }, T{ option.T }, St{ option.St }, r{ option.r }, sigma{ option.sigma }{}
	LookbackOption& LookbackOption::operator=(const LookbackOption& option) {
		if (this == &option)
			return *this;
		t = option.t;
		T = option.T;
		St = option.St;
		r = option.r;
		sigma = option.sigma;
		return *this;
	}
	double LookbackOption::estimate_price(const Matrix& normSimuls) const {
		double price_estimate{ 0 }, payoff_estimate{ 0 };
		int M = normSimuls.get_M();
		std::vector<double> simulation{};
		double Pt = exp(-r * (T - t));
		for (int i{ 0 }; i < M; ++i) {
			simulation = normSimuls(i);
			payoff_estimate += this->simulate_payoff(simulation);
		}
		payoff_estimate /= M; //payoffestimate
		price_estimate = Pt * payoff_estimate; //discount to get price estimate
		return price_estimate;
	}
}