
NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = mlx
MLX_FLAGS = -L/usr/include -lXext -lX11 -lm
MLX_LIB = $(MLX_DIR)/libmlx.a

SRC = main.c \
	  events.c \
	  exit.c \
	  free_split.c \
	  load_images.c \
	  map.c \
	  map_checker.c \
	  path_check.c \
	  render.c \
	  utilities.c\
	  render_utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
