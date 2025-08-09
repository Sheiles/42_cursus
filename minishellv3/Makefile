NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = minishell.c parser.c executor.c redir.c heredoc.c builtin.c expansion.c env.c utils.c
OBJ = $(SRC:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lreadline -o $@ $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
