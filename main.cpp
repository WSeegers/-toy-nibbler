#include "Core.hpp"

#include <iostream>
#include <libgen.h>

const uint width = 50;
const uint height = 50;

int main(int ac, char *av[])
{

	NibblerEngine ne(dirname(av[0]), width, height);
}
