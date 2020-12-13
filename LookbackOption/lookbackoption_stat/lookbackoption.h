#ifndef LOOKBACKOPTION_H
#define LOOKBACKOPTION_H

#include <vector>

namespace lookback {

	class LookbackOption {
	protected:
		double t; //current date
		double T; //maturity
		double St; 
		double r;
		double sigma;
	public:
		LookbackOption(double t_,double T_,double St_,double r_,double sigma_);
		LookbackOption(const LookbackOption& option);
		LookbackOption& operator=(const LookbackOption& option);
		virtual ~LookbackOption() {};

		double get_t() const { return t; }
		double get_T() const { return T; }
		double get_St() const { return St; }
		double get_r() const { return r; }
		double get_sigma() const { return sigma; }

		LookbackOption& set_t(double t_) { t = t_; return *this; }
		LookbackOption& set_T(double T_) { T = T_; return *this; }
		LookbackOption& set_St(double St_) { St = St_; return *this; }
		LookbackOption& set_r(double r_) { r = r_; return *this; }
		LookbackOption& set_sigma(double sigma_) { sigma = sigma_; return *this; }

		virtual double analytical_price() const = 0;
		virtual double simulate_payoff(std::vector<double> normSimulation) const = 0;
		virtual LookbackOption* copy() const = 0;
	};
}
#endif // !LOOKBACKOPTION_H

