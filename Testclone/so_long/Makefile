NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = mlx
PRINTF_DIR = ft_printf
LIBFT_DIR = libft

MLX_LIB = $(MLX_DIR)/libmlx.a
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MLX_FLAGS = -L/usr/include -lXext -lX11 -lm

SRC = main.c \
      events.c \
      exit.c \
      free_split.c \
      load_images.c \
      map.c \
      map_checker.c \
      path_check.c \
      render.c \
      utilities.c \
      render_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(PRINTF_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(PRINTF_LIB) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(PRINTF_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
