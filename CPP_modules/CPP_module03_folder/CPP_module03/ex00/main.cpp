#include <iostream>
#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap trap("Bender");
	
	trap.attack("Fry");
	trap.takeDamage(5);
	trap.beRepaired(3);
	
	for (int i = 0; i < 10; i++)
		trap.attack("Fry");
	
	trap.attack("Fry");

	return 0;
}
