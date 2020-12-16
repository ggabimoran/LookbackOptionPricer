#include "interface.h"
#include "lookbackoption_dll.h"

DLL_EXPORT int __stdcall C_execute(double t, double T, char *type, double St, double r, double sigma, int M, int N) {
	return lookback::execute(t, T, type, St, r, sigma, M, N);
}




