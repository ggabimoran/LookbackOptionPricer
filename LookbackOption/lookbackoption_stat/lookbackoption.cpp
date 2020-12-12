#include "lookbackoption.h"

namespace lookback {
	LookbackOption::LookbackOption(double t_, double T_, double St_, double r_, double sigma_) 
		: t{ t_ }, T{ T_ }, St{ St_ }, r{ r_ }, sigma{ sigma_ }{}
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
}