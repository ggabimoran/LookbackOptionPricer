#ifndef LOOKBACKPUT_H
#define LOOKBACKPUT_H

#include "lookbackoption.h"

namespace lookback {
	class LookbackPut : public LookbackOption {
	public:
		virtual double analytical_price();
		virtual double simulate_payoff(std::vector<double> normSimulation);
	};
}

#endif // !LOOKBACKPUT_H
