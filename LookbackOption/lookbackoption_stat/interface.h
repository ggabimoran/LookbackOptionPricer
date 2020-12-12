#ifndef INTERFACE_H
#define INTERFACE_H

#include "lookbackcall.h"
#include "lookbackput.h"
#include "greeks.h"
#include "matrix.h"

#include <vector>
#include <string>



namespace lookback{

	typedef struct{
		double P; // theoretical price
		std::vector<double> greeks; //greeks
		std::vector<double> prices; //option prices as a function of the underlying share
		std::vector<double> deltas; //option deltas as a function of the underlying share
		double execution_time; // program execution time
	} Results;
	
	//calls functions from greeks.h
	std::vector<double> compute_greeks(LookbackOption& option, const Matrix& normSimuls);

	//creates Lookbackcall/Lookbackput based on type value, then calls analytical_price() member for P
	// Then create Matrix of normal distribution simulations of size N,M and 
	//calls 3 functions above to create Results struct
	Results execute(double t,double T,std::string type,double St,double r,double sigma, int M, int N);
}

#endif // !INTERFACE_H

