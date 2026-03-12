#include <iostream>
#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap trap("Bender");
	
	trap.attack("Fry");
	trap.takeDamage(5);
	trap.beRepaired(3);
	
	int i = 0;
	while (i < 10)
	{
		trap.attack("Fry");
		i++;
	}
	
	trap.attack("Fry");

	return 0;
}
