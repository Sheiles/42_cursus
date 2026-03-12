#ifndef DOG_HPP
# define DOG_HPP

# include "AAnimal.hpp"
# include "Brain.hpp"

class Dog : public AAnimal
{
private:
	Brain* brain;

public:
	Dog(void);
	Dog(const Dog &copy);
	Dog &operator=(const Dog &rhs);
	~Dog(void);

	void makeSound(void) const;
};

#endif
