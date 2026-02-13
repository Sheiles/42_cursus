NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = \
minishell.c \
executor.c \
redir.c \
expansion.c \
parser.c \
parser_utils.c \
utils.c \
env_init.c env_getset.c env_array.c env_free.c \
builtin_echo.c builtin_cd_pwd.c builtin_env_export.c builtin_unset_exit.c builtin_dispatch.c \
parser_tok.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lreadline -o $@ $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
