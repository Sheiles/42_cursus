#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main(void)
{
	std::cout << "=== Creating ClapTrap ===" << std::endl;
	ClapTrap clap("Clappy");
	
	std::cout << "\n=== Creating ScavTrap ===" << std::endl;
	ScavTrap scav("Scavvy");
	
	std::cout << "\n=== Testing ScavTrap ===" << std::endl;
	scav.attack("Enemy");
	scav.takeDamage(30);
	scav.beRepaired(10);
	scav.guardGate();
	
	std::cout << "\n=== Testing ClapTrap ===" << std::endl;
	clap.attack("Enemy");
	clap.takeDamage(5);
	clap.beRepaired(2);
	
	std::cout << "\n=== Destruction ===" << std::endl;
	return 0;
}
