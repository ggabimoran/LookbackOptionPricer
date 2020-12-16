#include "interface.h"
#include <fstream>

namespace lookback {
	std::vector<double> compute_greeks(const LookbackOption& option, const Matrix& normSimuls) {
		std::vector<double> greeks = std::vector<double>(5);
		greeks[0] = Greeks::delta(option, normSimuls);
		greeks[1] = Greeks::gamma(option, normSimuls);
		greeks[2] = Greeks::vega(option, normSimuls);
		greeks[3] = Greeks::rho(option, normSimuls);
		greeks[4] = Greeks::theta(option, normSimuls);
		return greeks;
	}
	int execute(double t, double T, std::string type, double St, double r, double sigma, int M, int N) {
		//sizeof(double) = 8, sizeof(int) = 4 and sizeof("call") = 5 , sum is 52 bytes
		try {
			clock_t tStart = clock(); //start time
			Results results{}; //initialize variables
			int n = 10;
			results.St_discretization = std::vector<double>(n);
			results.M = M;
			results.N = N;
			results.option_type = type;
			double St_max = 2 * St;
			double St_min = St / 2; // !! St cannot be equal to 0
			double payoff_estimate;
			Matrix normSimuls{ M,N };
			LookbackCall call{ t,T,St,r,sigma };
			LookbackPut put{ t,T,St,r,sigma };
			LookbackOption* option{ &call };
			if (type.compare("put") == 0) option = &put;

			results.greeks = compute_greeks(*option, normSimuls); //compute option greeks
			results.P = option->analytical_price(); //compute option analytical price

			results.deltas = results.St_discretization; //compute deltas, prices for St discretization
			results.prices = results.St_discretization;
			double Pt = exp(-option->get_r() * (option->get_T() - option->get_t()));
			for (int k{ 0 }; k < n; ++k) { // for each St value
				normSimuls = Matrix{ M,N }; // instantiate new matrix of normal simulations
				results.St_discretization[k] = St_min + (St_max - St_min) * k / n;
				option->set_St(results.St_discretization[k]); // set St
				results.deltas[k] = Greeks::delta(*option, normSimuls); //compute delta
				payoff_estimate = 0; //compute price estimate as empirical mean of M simulated payoffs
				for (int i{ 0 }; i < M; ++i) {
					payoff_estimate += Pt * option->simulate_payoff(normSimuls(i));
				}
				payoff_estimate /= M;
				results.prices[k] = payoff_estimate;
			}
			option->set_St(St);

			clock_t tEnd = clock(); //end time
			results.execution_time = static_cast<double>(tEnd - tStart) / CLOCKS_PER_SEC; //compute execution time
			write_to_csv(option, &results);
		}
		catch (const std::exception &exception) {
			write_to_csv(nullptr,nullptr,exception.what());
			return 1;
		}
		return 0; //return results struct
	}

	int write_to_csv(LookbackOption *option, Results *results, std::string error_message) {
		std::ofstream myfile ("results.csv");
		myfile << error_message << "\n";
		if (error_message.compare("") != 0) return 1;
		myfile << "Results for floating lookback option with parameters :\n";
		myfile << "t;T;Option type;St;r;sigma;M;N;St_Discretization\n";
		myfile << option->get_t() << ';' << option->get_T() << ';' << results->option_type << ';' << option->get_St() << ';';
		myfile << option->get_r() << ';' << option->get_sigma() << ';' << results->M << ';' << results->N << ';' << results->St_discretization.size() << "\n";
		myfile << "Execution time :\n";
		myfile << results->execution_time << "s\n";
		myfile << "Theoretical price :\n";
		myfile << results->P << "\n";
		myfile << "Delta;Gamma;Vega;Rho;Theta\n";
		myfile << results->greeks[0] << ';' << results->greeks[1] << ';' << results->greeks[2] << ';' << results->greeks[3] << ';' << results->greeks[4] << "\n";
		
		int n = results->St_discretization.size();
		myfile << "St discretization :\n";
		for (int i{ 0 }; i < n; ++i)
			myfile << results->St_discretization[i] << ';';
		myfile << "\n";
		myfile << "Estimated prices wrt St :\n";
		for (int i{ 0 }; i < n; ++i)
			myfile << results->prices[i] << ';';
		myfile << "\n";
		myfile << "Estimated deltas wrt St :\n";
		for (int i{ 0 }; i < n; ++i)
			myfile << results->deltas[i] << ';';
		myfile << "\n";
		myfile.close();
		return 0;
	}
}