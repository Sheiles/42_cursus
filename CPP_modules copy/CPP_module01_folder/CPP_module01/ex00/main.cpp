#include "Zombie.hpp"

int main(void)
{
	
	randomChump("StackZombie");

	
	Zombie* heapZombie = newZombie("HeapZombie");
	heapZombie->announce();
	delete heapZombie;

	return 0;
}
