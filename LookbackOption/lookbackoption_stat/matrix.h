#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <random>
#include <iostream>
#include <chrono>

namespace lookback {
	enum class MatrixInitialization {
		none,//zero initialize
		standard_normal
	};

	class Matrix {
	private:
		int M_, N_;
		std::vector<double> data; //access i,j element with data[i*N + j]
	public:
		Matrix(int M, int N, MatrixInitialization init=MatrixInitialization::standard_normal); 
		virtual ~Matrix() {};
		double operator()(int i, int j) const;
		std::vector<double> operator()(int i) const; //get line i of the matrix
		friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
	};
}

#endif // !MATRIX_H

