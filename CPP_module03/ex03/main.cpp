#include <iostream>
#include "DiamondTrap.hpp"

int main(void)
{
	std::cout << "=== Creating DiamondTrap ===" << std::endl;
	DiamondTrap diamond("Diamond");
	
	std::cout << "\n=== Testing DiamondTrap ===" << std::endl;
	diamond.attack("Enemy");
	diamond.takeDamage(20);
	diamond.beRepaired(10);
	diamond.whoAmI();
	diamond.guardGate();
	diamond.highFivesGuys();
	
	std::cout << "\n=== Destruction ===" << std::endl;
	return 0;
}
