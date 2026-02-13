#include "Zombie.hpp"
#include <iostream>

int main(void)
{
	int hordeSize = 5;
	Zombie* horde = zombieHorde(hordeSize, "Zombie");

	for (int i = 0; i < hordeSize; i++)
		horde[i].announce();

	delete[] horde;

	return 0;
}
