#ifndef GREEKS_H
#define GREEKS_H

namespace lookback {
	class Greeks {
	private:
		static double alpha; // finesse de l'approximation de la dérivée
		//si tous les calculs des greeks prennent la même forme, on pourrait essayer de tout centraliser en une fonction (à voir)
		static double derivee(const LookbackOption& option, const Matrix& normSimuls);
	public:
		static double delta(const LookbackOption& option, const Matrix& normSimuls);
		static double gamma(const LookbackOption& option, const Matrix& normSimuls);
		static double vega(const LookbackOption& option, const Matrix& normSimuls);
		static double rho(const LookbackOption& option, const Matrix& normSimuls);
		static double theta(const LookbackOption& option, const Matrix& normSimuls);
	};
	double Greeks::alpha{ 0.01 };
}

#endif // !GREEKS_H
