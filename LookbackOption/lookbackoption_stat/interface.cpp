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

	void execute_init_results(Results *res, std::string type, int M, int N, int n) {
		res->St_discretization = std::vector<double>(n);
		res->M = M;
		res->N = N;
		res->option_type = type;
		res->deltas = res->St_discretization; 
		res->prices = res->St_discretization;
	}

	void compute_discretization_vals(Results *results, LookbackOption *option, Matrix& normSimuls, double St, int M, int N, int n) {
		double St_max{ 2 * St }, St_min{ St / 2 }, price_estimate{ 0 }, Pt{ exp(-option->get_r() * (option->get_T() - option->get_t())) };
		for (int k{ 0 }; k < n; ++k) { // for each St value
			normSimuls = Matrix{ M,N }; // instantiate new matrix of normal simulations
			results->St_discretization[k] = St_min + (St_max - St_min) * k / n;
			option->set_St(results->St_discretization[k]); // set St
			results->deltas[k] = Greeks::delta(*option, normSimuls); //compute delta
			price_estimate = 0; //compute price estimate as empirical mean of M simulated payoffs discounting with Pt
			for (int i{ 0 }; i < M; ++i) {
				price_estimate += Pt * option->simulate_payoff(normSimuls(i));
			}
			price_estimate /= M;
			results->prices[k] = price_estimate;
		}
		option->set_St(St);
	}

	int execute(double t, double T, std::string type, double St, double r, double sigma, int M, int N) {
		try {
			clock_t tStart = clock(); //start time
			Results results{}; 
			int n = 10;
			execute_init_results(&results, type, M, N, n);
			Matrix normSimuls{ M,N };
			LookbackCall call{ t,T,St,r,sigma };
			LookbackPut put{ t,T,St,r,sigma };
			LookbackOption* option{ &call };
			if (type.compare("put") == 0) option = &put;

			results.greeks = compute_greeks(*option, normSimuls); //compute option greeks
			results.P = option->analytical_price(); //compute option analytical price
			compute_discretization_vals(&results, option, normSimuls, St, M, N, n);

			clock_t tEnd = clock(); //end time
			results.execution_time = static_cast<double>(tEnd - tStart) / CLOCKS_PER_SEC; //compute execution time
			write_to_csv(option, &results);
		}
		catch (const std::exception &exception) {
			write_to_csv(nullptr,nullptr,exception.what());
			return 1;
		}
		return 0; 
	}

	int write_error_message(std::ofstream& myfile, std::string error_message) {
		myfile << error_message << "\n";
		if (error_message.compare("") != 0) return 1;
		else return 0;
	}

	void write_option_params(std::ofstream& myfile, LookbackOption *option, Results *results) {
		myfile << "Results for floating lookback option with parameters :\n";
		myfile << "t;T;Option type;St;r;sigma;M;N;St_Discretization\n";
		myfile << option->get_t() << ';' << option->get_T() << ';' << results->option_type << ';' << option->get_St() << ';';
		myfile << option->get_r() << ';' << option->get_sigma() << ';' << results->M << ';' << results->N << ';' << results->St_discretization.size() << "\n";
	}

	void write_execution_time(std::ofstream& myfile, Results *results) {
		myfile << "Execution time :\n";
		myfile << results->execution_time << "s\n";
	}

	void write_theoretical_P(std::ofstream& myfile, Results *results) {
		myfile << "Theoretical price :\n";
		myfile << results->P << "\n";
	}

	void write_greeks(std::ofstream& myfile, Results *results) {
		myfile << "Delta;Gamma;Vega;Rho;Theta\n";
		myfile << results->greeks[0] << ';' << results->greeks[1] << ';' << results->greeks[2] << ';' << results->greeks[3] << ';' << results->greeks[4] << "\n";
	}

	void write_discretization_vals(std::ofstream& myfile, Results *results) {
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
	}

	int write_to_csv(LookbackOption *option, Results *results, std::string error_message) {
		std::ofstream myfile ("results.csv");
		if (write_error_message(myfile, error_message)) return 1;
		write_option_params(myfile,option,results);
		write_execution_time(myfile, results);
		write_theoretical_P(myfile, results);
		write_greeks(myfile, results);
		write_discretization_vals(myfile, results);
		myfile.close();
		return 0;
	}
}