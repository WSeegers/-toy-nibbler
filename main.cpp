#include "Core.hpp"

#include <iostream>
#include <libgen.h>

const uint WIDTH = 50;
const uint HEIGHT = 50;

const int MIN_DIM = 10;
const int MAX_DIM = 50;

bool parseDimensions(uint &width, uint &height, std::string arg_width, std::string arg_height)
{
	int iwidth = std::stoi(arg_width);
	int iheight = std::stoi(arg_height);

	if (iwidth < MIN_DIM || iwidth > MAX_DIM || iheight < MIN_DIM || iheight > MAX_DIM)
	{
		std::cout << "Error: Dimensions must be in a range of "
				  << MIN_DIM << " - " << MAX_DIM << std::endl;
		return true;
	}

	width = iwidth;
	height = iheight;
	return false;
}

void printUsage()
{
	std::cout << "Usage ./nibler [width height]" << std::endl;
}

int main(int ac, char *av[])
{
	uint width = WIDTH;
	uint height = HEIGHT;
	bool error = false;

	switch (ac)
	{
	case 1:
		break;
	case 3:
		error = parseDimensions(width, height, std::string(av[1]), std::string(av[2]));
		break;
	default:
		error = true;
		printUsage();
		break;
	}
	if (error)
		return 1;

	NibblerEngine ne(dirname(av[0]), width, height);
	return 0;
}
