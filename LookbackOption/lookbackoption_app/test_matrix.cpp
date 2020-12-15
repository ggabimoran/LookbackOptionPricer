#include "test_matrix.h"

namespace lookback {
	void test_matrix() {
		Matrix m1{ 3,3 };
		Matrix m2{ 1,2,MatrixInitialization::none};
		Matrix m3{ 4,2,MatrixInitialization::standard_normal};
		//Matrix m4{ -1,4 }; // exception thrown
		//Matrix m5{ 5,-3 }; // exception thrown
		//Matrix m6{ -2,-2 }; // exception thrown

		std::cout << m1 << '\n';
		std::cout << m2 << '\n';
		std::cout << m3;

		std::cout << m1.get_M() << ' ' << m1.get_N() << '\n';
		std::cout << m2.get_M() << ' ' << m2.get_N() << '\n';
		std::cout << m3.get_M() << ' ' << m3.get_N() << '\n';

		std::cout << m1(0, 2) << '\n';
		std::cout << m3(1, 1) << '\n';
		std::cout << m1(0, 0) << '\n';
		std::cout << m3(3, 1) << '\n';
		std::cout << m1(2, 2) << '\n';
		std::cout << m3(0, 1) << '\n';

		//std::cout << m1(-1, 1) << '\n'; //exception thrown
		//std::cout << m3(0, 4) << '\n'; //exception thrown

		std::vector<double> v1 = m1(0);
		std::vector<double> v2 = m3(0);
		for (int i{ 0 }; i < v1.size(); ++i)
			std::cout << v1[i] << ' ';
		std::cout << '\n';
		for (int i{ 0 }; i < v2.size(); ++i)
			std::cout << v2[i] << ' ';
		std::cout << '\n';

		//std::vector<double> v4 = m3(-1);  //exception thrown
		//std::vector<double> v3 = m1(5); //exception thrown

		std::cout << '\n' << '\n';
		double execution_time;

		clock_t tStart = clock();
		Matrix m100{ 100,100 };
		clock_t tEnd = clock();
		execution_time = static_cast<double>(tEnd - tStart) / CLOCKS_PER_SEC;
		std::cout << "Execution time to simulate 100 * 100 gaussians: " << execution_time << 's' << '\n';

		std::cout << '\n' << '\n';

		tStart = clock();
		Matrix m1000{ 1000,1000 };
		tEnd = clock();
		execution_time = static_cast<double>(tEnd - tStart) / CLOCKS_PER_SEC;
		std::cout << "Execution time to simulate 1000 * 1000 gaussians: " << execution_time << 's' << '\n';
		
	}
}