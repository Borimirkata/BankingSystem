#include <iostream>
#include "System.h"
#include "BankingSystem.h"


int main() {
	try {
		run();
	}
	catch (std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "invalid argument given" << std::endl;
	}

	return 0;
}