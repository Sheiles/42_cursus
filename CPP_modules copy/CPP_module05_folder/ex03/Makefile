NAME    = bureaucrat
CXX     = c++
CXXFLAGS= -Wall -Wextra -Werror -std=c++98

SRCS    = main.cpp Bureaucrat.cpp AForm.cpp ShrubberyCreationForm.cpp \
          RobotomyRequestForm.cpp PresidentialPardonForm.cpp Intern.cpp
OBJS    = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

main.o: AForm.hpp Bureaucrat.hpp Intern.hpp
Bureaucrat.o: Bureaucrat.hpp AForm.hpp
AForm.o: AForm.hpp Bureaucrat.hpp
ShrubberyCreationForm.o: ShrubberyCreationForm.hpp AForm.hpp
RobotomyRequestForm.o: RobotomyRequestForm.hpp AForm.hpp
PresidentialPardonForm.o: PresidentialPardonForm.hpp AForm.hpp
Intern.o: Intern.hpp AForm.hpp ShrubberyCreationForm.hpp \
          RobotomyRequestForm.hpp PresidentialPardonForm.hpp

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
