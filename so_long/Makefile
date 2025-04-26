
NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = mlx
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

SRC = main.c \
      map.c \
      events.c \
      render.c \
      utils.c \
      load_images.c \
      path_check.c \
      exit.c \
      free_split.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(MLX_DIR) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all