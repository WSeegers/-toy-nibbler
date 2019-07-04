#include "Core.hpp"

#include <iostream>
#include <libgen.h>

int main(int ac, char *av[])
{
	NibblerEngine ne(dirname(av[0]));
}
