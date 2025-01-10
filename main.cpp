#include <iostream>
#include <ctime>

#include "play.h"

int main(int argc, const char* argv[])
{
	playPoker(std::cin, std::cout, time(nullptr));

	return 0;
}