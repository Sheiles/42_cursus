
NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -lmlx -framework OpenGL -framework AppKit

SRC = main.c \
	  event.c \
	  exit.c \
	  free_split.c \
	  load_image.c \
	  map.c \
	  map_checker.c \
	  path_check.c \
	  render.c \
	  utilities.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
