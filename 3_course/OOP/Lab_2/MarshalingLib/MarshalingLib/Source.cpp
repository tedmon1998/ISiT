#include <iostream>
#include <string>
#include <comdef.h>


int calc(int money)
{
	std::cout << "Start computing";
	return money * 4 / 3 + 1;
}

extern "C" __declspec(dllexport) int Calcul(int CurrentExchangeRate);

int Calcul(int CurrentExchangeRate)
{
	return calc(CurrentExchangeRate);
}