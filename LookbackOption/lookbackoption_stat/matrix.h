#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

namespace lookback {
	class Matrix {
	private:
		int N_, M_;
		std::vector<std::vector<double>> data;
	public:
		//if normalInit true initialize with a standard normal distribution simulation for each component
		Matrix(int N, int M, bool normalInit=true); 
	};
}

#endif // !MATRIX_H

