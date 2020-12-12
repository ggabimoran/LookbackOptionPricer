#include "lookbackput.h"
#include "utils.h"

namespace lookback {
	double LookbackPut::analytical_price() const{
		double r1 = r + pow(sigma, 2.0) / 2;
		double tau = T - t;
		double d1 = r1 * sqrt(tau) / sigma;
		double d2 = d1 - sigma * sqrt(tau);
		double Pt = exp(-r * tau);
		double C = pow(sigma, 2.0) / (2 * r);
		double LPt = St * (-normalCDF(-d1) + Pt * normalCDF(-d2) + C * normalCDF(d1) - C * Pt * normalCDF(-d2));
		return LPt;
	}
	double LookbackPut::simulate_payoff(std::vector<double> normSimulation) const{
		int N = normSimulation.size();
		double ST = St;
		double MT = St; //max
		double C = r - pow(sigma, 2.0) / 2;
		double h = T / N;
		double variation = 1;
		double payoff = 0;
		for (int j{ 0 }; j < N; ++j) {
			variation = exp(C * h + normSimulation[j] * sigma * sqrt(h));
			ST *= variation;
			if (variation > 1)
				MT = ST;
		}
		payoff = MT - ST;
		return payoff;
	}
}