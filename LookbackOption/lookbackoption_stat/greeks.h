#ifndef GREEKS_H
#define GREEKS_H

#include "lookbackoption.h"
#include "matrix.h"

namespace lookback {
	enum class Greek_type {
		delta,
		gamma,
		vega,
		rho,
		theta
	};
	class Greeks {
	private:
		static double alpha; // finesse de l'approximation de la dérivée
		//si tous les calculs des greeks prennent la même forme, on pourrait essayer de tout centraliser en une fonction (à voir)
		static double derivative_approx(const LookbackOption& option, const Matrix& normSimuls,Greek_type type);
	public:
		static double delta(const LookbackOption& option, const Matrix& normSimuls);
		static double gamma(const LookbackOption& option, const Matrix& normSimuls);
		static double vega(const LookbackOption& option, const Matrix& normSimuls);
		static double rho(const LookbackOption& option, const Matrix& normSimuls);
		static double theta(const LookbackOption& option, const Matrix& normSimuls);
	};
}

#endif // !GREEKS_H
