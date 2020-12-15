#include "lookbackcall.h"
#include <cmath>

namespace lookback {
	double LookbackCall::analytical_price() const{
		auto normCDF{ [](double value) {return 0.5 * erfc(-value * sqrt(0.5)); } };
		double r1 = r + pow(sigma, 2.0) / 2;
		double tau = T - t;
		double d1 = r1 * sqrt(tau) / sigma;
		double d2 = d1 - sigma * sqrt(tau);
		double Pt = exp(-r * tau);
		double C = pow(sigma, 2.0) / (2 * r);
	    double LCt = St * (normCDF(d1) - Pt * normCDF(d2) - C * normCDF(-d1) + C * Pt * normCDF(d2));
		return LCt;
	}
	double LookbackCall::simulate_payoff(std::vector<double> normSimulation) const{
		int N = normSimulation.size();
		double ST = St;
		double mT = St; //min
		double C = r - pow(sigma, 2.0) / 2;
		double h = T / N;
		double std = sigma * sqrt(h);
		double variation=1;
		double payoff = 0;
		for (int j{ 0 }; j < N; ++j) {
			variation = exp(C * h + normSimulation[j] * std);
			ST *= variation;
			if (ST < mT)
				mT = ST;
		}
		payoff = ST - mT;
		return payoff;
	}
}