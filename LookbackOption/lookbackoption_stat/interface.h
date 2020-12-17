#ifndef INTERFACE_H
#define INTERFACE_H

#include "lookbackcall.h"
#include "lookbackput.h"
#include "greeks.h"
#include "matrix.h"

#include <vector>
#include <string>


/**
 *namespace used for lookbackoption_app to avoid naming collisions
 */
namespace lookback{
	/**
	 *struct Results
	 *contains program results 
	 */
	typedef struct{
		/// theoretical price
		double P; 
		// monte carlo P
		double MC_P;
		///greeks
		std::vector<double> greeks; 
		///option prices as a function of the underlying share
		std::vector<double> prices; 
		///option deltas as a function of the underlying share
		std::vector<double> deltas;
		/// program execution time
		double execution_time; 
		/// St discretization values
		std::vector<double> St_discretization;
		/// option type "call" or "put"
		std::string option_type;
		/// Monte Carlo parameter: number of simulations
		int M;
		/// Monte Carlo parameter: temporal discretization
		int N;
	} Results;

	typedef struct {
		std::vector<double> theoretical; /// M copies of analytical price P
		std::vector<double> MC_evolution; ///MC evolution wrt M
	} Convergence;
	
	/**
	 *computes option greeks for given option and standard normal simulations
	 *
	 *@param option pointer to lookback call or put object
	 *@param normSimuls standard normal simulations
	 *@return vector containing delta,gamma,vega,rho and theta
	 */
	std::vector<double> compute_greeks(const LookbackOption& option, const Matrix& normSimuls);

	/**
	 *execute program
	 *
	 *@param double t current time
	 *@param double T maturity
	 *@param std::string type call or put
	 *@param double St stock price at time t
	 *@param double double r risk-free rate
	 *@param double sigma stock volatility
	 *@param int M Monte Carlo parameter for number of simulations
	 *@param double Monte Carlo parameter for temporal discretization
	 *@return 0 for correct execution, 1 if an exception is thrown
	 */
	int execute(double t,double T,std::string type,double St,double r,double sigma, int M, int N);
	///intialize results struct
	void execute_init_results(Results *res, std::string type, int M, int N, int n);
	///compute estimated price and deltas by monte carlo for each St
	void compute_discretization_vals(Results *results, LookbackOption *option, Matrix& normSimuls, double St, int M, int N, int n);

	/**
	 *write execute output to csv file
	 *
	 *@param option pointer to lookback call or put object
	 *@param results pointer to results struct
	 *@param error_message, default value means no exceptions where caught
	 *@return 1 if error , 0 else
	 */
	int write_to_csv(LookbackOption *option, Results *results, std::string error_message="");
	///write error message to csv
	int write_error_message(std::ofstream& myfile, std::string error_message);
	///write option params to csv
	void write_option_params(std::ofstream& myfile, LookbackOption *option, Results *results);
	///write execution time to csv
	void write_execution_time(std::ofstream& myfile, Results *results);
	///write theoretical price to csv
	void write_theoretical_P(std::ofstream& myfile, Results *results);
	///write monte carlo price
	void write_MC_P(std::ofstream& myfile, Results *results);
	///write greeks to csv
	void write_greeks(std::ofstream& myfile, Results *results);
	///write discretization vals to csv
	void write_discretization_vals(std::ofstream& myfile, Results *results);

	int execute_convergence(double t, double T, std::string option_type, double St, double r, double sigma, int N, std::string convergence_type);
	void compute_MC_price_evolution(Convergence *convergence, LookbackOption* option, const Matrix& normSimuls);
	int write_convergence_to_csv(Convergence *convergence, std::string error_message="");
	void compute_convergence(Convergence *convergence, LookbackOption *option, const Matrix& normSimuls, std::string convergence_type, std::string option_type);
	void compute_MC_greek_evolution(Convergence *convergence, LookbackOption* option, const Matrix& normSimuls, Greek_type type);

}

#endif // !INTERFACE_H

