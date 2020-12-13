#ifndef LOOKBACKPUT_H
#define LOOKBACKPUT_H

#include "lookbackoption.h"

namespace lookback {
	class LookbackPut : public LookbackOption {
	public:
		LookbackPut(double t, double T, double St, double r, double sigma) : LookbackOption(t, T, St, r, sigma) {};
		LookbackPut(const LookbackPut& put) : LookbackOption(put) {};
		LookbackPut& operator=(const LookbackPut& put) { LookbackOption::operator=(put); }
		virtual ~LookbackPut() {};
		virtual double analytical_price() const override;
		virtual double simulate_payoff(std::vector<double> normSimulation) const override;
		virtual LookbackOption* copy() const override { return new LookbackPut(*this); }
	};
}

#endif // !LOOKBACKPUT_H
