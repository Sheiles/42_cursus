#include "Zombie.hpp"

int main(void)
{
	// Stack allocated zombie
	randomChump("StackZombie");

	// Heap allocated zombie
	Zombie* heapZombie = newZombie("HeapZombie");
	heapZombie->announce();
	delete heapZombie;

	return 0;
}
