#include "interface.h"
#include "lookbackoption_dll.h"

DLL_EXPORT int __stdcall C_execute(double t, double T, char *type, double St, double r, double sigma, int M, int N) {
	return lookback::execute(t, T, type, St, r, sigma, M, N);
}
DLL_EXPORT int __stdcall C_execute_convergence(double t, double T, char *option_type, double St, double r, double sigma, int N, char *convergence_type) {
	return lookback::execute_convergence(t, T, option_type, St, r, sigma, N, convergence_type);
}



