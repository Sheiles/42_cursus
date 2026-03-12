#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"

class Cat : public Animal
{
public:
	Cat(void);
	Cat(const Cat &copy);
	Cat &operator=(const Cat &rhs);
	~Cat(void);

	void makeSound(void) const;
};

#endif
