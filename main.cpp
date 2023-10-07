#include "Calculator.h"

int main()
{
	const std::string expression { "log5(10)" };

	try
	{
		std::cout << std::fixed << calculator::eval<double>(expression) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}