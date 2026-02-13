#ifndef AANIMAL_HPP
# define AANIMAL_HPP

# include <string>
# include <iostream>

class AAnimal
{
protected:
	std::string type;

public:
	AAnimal(void);
	AAnimal(const AAnimal &copy);
	AAnimal &operator=(const AAnimal &rhs);
	virtual ~AAnimal(void);

	virtual void makeSound(void) const = 0;
	std::string getType(void) const;
};

#endif
