#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

namespace lookback {
	class Matrix {
	private:
		int N_, M_;
		std::vector<std::vector<double>> data;
	public:
		Matrix(int N, int M);
	};
}

#endif // !MATRIX_H

