#ifndef LOOKBACKCALL_H
#define LOOKBACKCALL_H

#include "lookbackoption.h"

namespace lookback {
	class LookbackCall : public LookbackOption {
	public:
		LookbackCall(double t, double T, double St, double r, double sigma) : LookbackOption(t, T, St, r, sigma) {};
		LookbackCall(const LookbackCall& call) : LookbackOption(call) {};
		LookbackCall& operator=(const LookbackCall& call) { LookbackOption::operator=(call); }
		virtual ~LookbackCall() {};
		virtual double analytical_price() const override;
		virtual double simulate_payoff(std::vector<double> normSimulation) const override;
		virtual LookbackOption* copy() const override { return new LookbackCall(*this); }
	};
}

#endif // !LOOKBACKCALL_H

