NAME    = bureaucrat
CXX     = c++
CXXFLAGS= -Wall -Wextra -Werror -std=c++98

SRCS    = main.cpp Bureaucrat.cpp Form.cpp
OBJS    = $(SRCS:.cpp=.o)

all: $(NAME)

main.o: main.cpp Bureaucrat.hpp Form.hpp
Bureaucrat.o: Bureaucrat.cpp Bureaucrat.hpp Form.hpp
Form.o: Form.cpp Form.hpp Bureaucrat.hpp

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
