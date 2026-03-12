#include <iostream>
#include "ClapTrap.hpp"
#include "FragTrap.hpp"

int main(void)
{
	std::cout << "=== Creating ClapTrap ===" << std::endl;
	ClapTrap clap("Clappy");
	
	std::cout << "\n=== Creating FragTrap ===" << std::endl;
	FragTrap frag("Fraggy");
	
	std::cout << "\n=== Testing FragTrap ===" << std::endl;
	frag.attack("Enemy");
	frag.takeDamage(30);
	frag.beRepaired(10);
	frag.highFivesGuys();
	
	std::cout << "\n=== Testing ClapTrap ===" << std::endl;
	clap.attack("Enemy");
	clap.takeDamage(5);
	clap.beRepaired(2);
	
	std::cout << "\n=== Destruction ===" << std::endl;
	return 0;
}
