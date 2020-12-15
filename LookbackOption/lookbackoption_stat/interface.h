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
		double* greeks; //greeks
		double* prices; //option prices as a function of the underlying share
		double* deltas; //option deltas as a function of the underlying share
		double execution_time; // program execution time
		int St_discretization;
	} Results;

	double* convert_std_vector(std::vector<double> v);
	
	//calls functions from greeks.h
	std::vector<double> compute_greeks(const LookbackOption& option, const Matrix& normSimuls);

	//creates Lookbackcall/Lookbackput based on type value, then calls analytical_price() member for P
	// Then create Matrix of normal distribution simulations of size N,M and 
	//calls 3 functions above to create Results struct
	Results execute(double t,double T,std::string type,double St,double r,double sigma, int M, int N);
}

#endif // !INTERFACE_H

