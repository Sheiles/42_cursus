NAME    = bureaucrat
CXX     = c++
CXXFLAGS= -Wall -Wextra -Werror -std=c++98

SRCS    = main.cpp Bureaucrat.cpp AForm.cpp ShrubberyCreationForm.cpp \
          RobotomyRequestForm.cpp PresidentialPardonForm.cpp
OBJS    = $(SRCS:.cpp=.o)

all: $(NAME)

main.o: main.cpp AForm.hpp Bureaucrat.hpp PresidentialPardonForm.hpp \
        RobotomyRequestForm.hpp ShrubberyCreationForm.hpp
Bureaucrat.o: Bureaucrat.cpp Bureaucrat.hpp AForm.hpp
AForm.o: AForm.cpp AForm.hpp Bureaucrat.hpp
ShrubberyCreationForm.o: ShrubberyCreationForm.cpp \
                         ShrubberyCreationForm.hpp AForm.hpp
RobotomyRequestForm.o: RobotomyRequestForm.cpp RobotomyRequestForm.hpp AForm.hpp
PresidentialPardonForm.o: PresidentialPardonForm.cpp \
                          PresidentialPardonForm.hpp AForm.hpp

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
