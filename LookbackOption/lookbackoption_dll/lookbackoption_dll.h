#ifndef LOOKBACKOPTION_DLL_H
#define LOOKBACKOPTION_DLL_H

#define DLL_EXPORT __declspec(dllexport)

#include "interface.h"

extern "C"
{
	DLL_EXPORT int __stdcall C_execute(double t, double T, char *type, double St, double r, double sigma, int M, int N);
}

#endif // !LOOKBACKOPTION_DLL_H

