#include "Zombie.hpp"
#include <iostream>

int main(void)
{
	int hordeSize = 5;
	Zombie* horde = zombieHorde(hordeSize, "Zombie");

	int i = 0;
	while (i < hordeSize)
	{
		horde[i].announce();
		i++;
	}

	delete[] horde;

	return 0;
}
