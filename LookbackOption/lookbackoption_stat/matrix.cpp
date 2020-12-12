#include "matrix.h"

namespace lookback {
	Matrix::Matrix(int M, int N, MatrixInitialization init) : M_{ M }, N_{ N }, data{std::vector<double>(M*N,0)} {
		switch (init) {
		case MatrixInitialization::standard_normal: {
			unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
			std::default_random_engine generator(seed);
			std::normal_distribution<double> distribution(0.0, 1.0);
			for (int i{ 0 }; i < M; ++i) {
				for (int j{ 0 }; j < N; ++j)
					data[i*N + j] = distribution(generator);
			}
		}
			break;
		case MatrixInitialization::none:
			break;
		}
	}
	double Matrix::operator()(int i, int j) const {
		return data[i*N_ + j];
	}
	std::vector<double> Matrix::operator()(int i) const {
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