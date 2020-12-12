#ifndef LOOKBACKCALL_H
#define LOOKBACKCALL_H

#include "lookbackoption.h"

namespace lookback {
	class LookbackCall : public LookbackOption {
	public:
		LookbackCall(double t, double T, double St, double r, double sigma) : LookbackOption(t, T, St, r, sigma) {};
		virtual ~LookbackCall() {};
		virtual double analytical_price() const override;
		virtual double simulate_payoff(std::vector<double> normSimulation) const override;
	};
}

#endif // !LOOKBACKCALL_H

