#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <string>

class Brain
{
private:
	std::string ideas[100];

public:
	Brain(void);
	Brain(const Brain &copy);
	Brain &operator=(const Brain &rhs);
	~Brain(void);

	void setIdea(int idx, const std::string &idea);
	std::string getIdea(int idx) const;
};

#endif
