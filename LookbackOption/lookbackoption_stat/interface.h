#ifndef INTERFACE_H
#define INTERFACE_H

#include "lookbackoption.h"
#include "greeks.h"

#include <vector>
#include <string>

namespace lookback{
	typedef struct{
		double P; // theoretical price
		std::vector<double> greeks; //greeks
		std::vector<double> prices; //option prices as a function of the underlying share
		std::vector<double> deltas; //option deltas as a function of the underlying share
	} Results;
	
	//calls functions from greeks.h
	std::vector<double> compute_greeks(const LookbackOption& option, int N, int M);

	//calls functions from loockbackoption.h
	std::vector<double> compute_prices(const LookbackOption& option, int N, int M);

	//calls function delta from greeks
	std::vector<double> compute_deltas(const LookbackOption& option, int N, int M);

	//creates Lookbackcall/Lookbackput based on type value, then calls analytical_price() member for P
	// and 3 functions above to create Results struct
	Results execute(double t,double T,std::string type,double S0,double r,double sigma, int N, int M);
}

#endif // !INTERFACE_H

