NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
INC_DIR = includes
PRINTF_DIR = ft_printf
LIBFT_DIR = libft


PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/init_stack.c \
	$(SRC_DIR)/errors.c \
	$(SRC_DIR)/free.c \
	$(SRC_DIR)/sort_small.c \
	$(SRC_DIR)/ops_swap.c \
	$(SRC_DIR)/ops_push.c \
	$(SRC_DIR)/ops_rotate.c \
	$(SRC_DIR)/ops_reverse_rotate.c \
	$(SRC_DIR)/utils_stack.c \
	$(SRC_DIR)/utils_convert.c \
	$(SRC_DIR)/utils_split.c \
	$(SRC_DIR)/assign_index.c \
	$(SRC_DIR)/sort_chunks.c\

OBJ = $(SRC:.c=.o)

all:$(ft_printf) $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(PRINTF_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $(NAME) $(OBJ) $(LIBFT_LIB) $(PRINTF_LIB)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(PRINTF_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(PRINTF_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all

.PHONY: all clean fclean re