#include "matrix.h"

namespace lookback {
	Matrix::Matrix(int M, int N, MatrixInitialization init) : M_{ M }, N_{ N }, data{std::vector<double>(M*N,0)} {
		if (M < 0 && N < 0) throw std::invalid_argument("Matrix dimensions must be positive");
		Init(init);
	}
	/**
	 *For standard normal initialization:
	 *System clock generates a seeding value, then instantiation of a random number engine class generates 
	 *pseudo-random numbers through its operator() member function. 
	 *The normal_distribution object transforms the values obtained this way so that successive calls to this member 
	 *function with the same arguments produce floating-point values that follow a Normal distribution with the 
	 *appropriate parameters (here standard normal).
	 *Antithetic variable is implemented to divide number of simulations in half.
	 *
	 *For none:
	 *Nothing to do, std vector is by default zero intialized
	 */
	void Matrix::Init(MatrixInitialization init) {
		switch (init) {
		case MatrixInitialization::standard_normal: {
			unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
			std::default_random_engine generator(seed);
			std::normal_distribution<double> distribution(0.0, 1.0);
			for (int i{ 0 }; i < M_; ++i) {
				for (int j{ 0 }; j < N_; ++j)
					data[i*N_ + j] = (j < (N_ + 1) / 2) ? distribution(generator) : -data[i*N_ + (N_ - 1 - j)];
			}
			break;
		}
		case MatrixInitialization::none:
			break;
		}
	}
	double Matrix::operator()(int i, int j) const {
		if (i < 0 || j < 0 || i >= M_ || j >= N_) throw std::out_of_range("Matrix element indexed out of range");
		return data[i*N_ + j];
	}
	std::vector<double> Matrix::operator()(int i) const {
		if (i < 0 || i >= M_ ) throw std::out_of_range("Matrix row indexed out of range");
		std::vector<double> row{std::vector<double>(N_)};
		for (int j{ 0 }; j < N_; ++j)
			row[j] = data[i*N_ + j];
		return row;
	}
	std::ostream& operator<<(std::ostream& out, const Matrix& m) {
		for (int i{ 0 }; i < m.M_; ++i) {
			for (int j{ 0 }; j < m.N_; ++j) {
				std::cout << m.data[i*m.N_ + j] << ' ';
			}
			std::cout << '\n';
		}
		return out;
	}
}