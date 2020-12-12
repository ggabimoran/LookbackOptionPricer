#include "utils.h"

namespace lookback {
	double normalCDF(double value) {
		double M_SQRT1_2 = sqrt(0.5);
		return 0.5 * erfc(-value * M_SQRT1_2);
	}
}