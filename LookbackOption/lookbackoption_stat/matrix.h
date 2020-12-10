#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

namespace lookback {
	class Matrix {
	private:
		int N_, M_;
		std::vector<double> data; //access i,j element with data[i*N + j]
	public:
		//if normalInit true initialize with a standard normal distribution simulation for each component
		Matrix(int N, int M, bool normalInit=true); 
		double operator()(int i, int j) const;
		double& operator()(int i, int j);
	};
}

#endif // !MATRIX_H

