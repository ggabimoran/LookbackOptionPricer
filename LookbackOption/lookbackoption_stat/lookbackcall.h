#ifndef LOOKBACKCALL_H
#define LOOKBACKCALL_H

#include "lookbackoption.h"

namespace lookback {
	class LookbackCall : public LookbackOption {
		virtual double analytical_price();
		virtual double simulate_payoff(std::vector<double> normSimulation);
	};
}

#endif // !LOOKBACKCALL_H

