#ifndef MATRIX_H
#define MATRIX_H

/**
 *Import relevant libraries
 */
#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <exception>
/**
 *namespace used for lookbackoption_app to avoid naming collisions
 */
namespace lookback {
	/**
	 *enum class to define the type of initialization for matrix elements
	 */
	enum class MatrixInitialization {
		/// Zero initialization
		none,
		/// Standard normal initilization
		standard_normal
	};
	/**
	 *class used for matrix modelling
	 *since standard initialization will mostly be used, no need for sparse implementation
	 */
	class Matrix {
	private:
		/// For Monte Carlo, M represents number of simulations, N spatial discretization
		int M_, N_;
		/// Signle std::vector containing all data, access i,j element with data[i*N + j]
		std::vector<double> data;
		/// initialization function 
		void Init(MatrixInitialization init);
	public:
		/*
		 *Parameterized constructor
		 *
		 *@throws std::invalid_argument if matrix dimensions are non-positive
		 *@param M row number
		 *@param N column number
		 *@param init enum for initialization specification
		 */
		Matrix(int M, int N, MatrixInitialization init=MatrixInitialization::standard_normal); 
		///Destructor
		virtual ~Matrix() {};
		///M getter
		int get_M() const { return M_; }
		///N getter
		int get_N() const { return N_;  }
		/*
		 *Const paranthesis operator overload to retrieve element
		 *
		 *@throws std::out_of_range if indexes are out of range
		 *@param i row index
		 *@param j column index
		 *@return double copy of matrix element i,j
		 */
		double operator()(int i, int j) const;
		/*
		 *Const paranthesis operator overload to retrieve row
		 *
		 *@throws std::out_of_range if index is out of range
		 *@param i row index
		 *@return std::vector<double> copy of matrix row i
		 */
		std::vector<double> operator()(int i) const; //get line i of the matrix
		/// output overload as a friend function
		friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
	};
}

#endif // !MATRIX_H

