#include "../inc/Util.h"

#include <iostream>
#include <random>

void Util::assertWithMessage(bool result, const std::string& message)
{
	if (!result)
	{
		std::cerr << message << std::endl;
		exit(1);
	}
}


int Util::randomOneOrMinus()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1);
	if (dist6(rng) == 0)
		return -1;
	return 1;
}

