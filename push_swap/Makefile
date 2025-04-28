
NAME = push_swap

SRC_DIR = src
INC_DIR = includes

SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/init_stack.c \
	$(SRC_DIR)/errors.c \
	$(SRC_DIR)/free.c \
	$(SRC_DIR)/sort_small.c \
	$(SRC_DIR)/sort_radix.c \
	$(SRC_DIR)/ops_swap.c \
	$(SRC_DIR)/ops_push.c \
	$(SRC_DIR)/ops_rotate.c \
	$(SRC_DIR)/ops_reverse_rotate.c \
	$(SRC_DIR)/utils_stack.c \
	$(SRC_DIR)/utils_convert.c \
	$(SRC_DIR)/utils_split.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re