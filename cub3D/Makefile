NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
DEBUGFLAGS	= -g -O0 -DDEBUG

LIBFT_DIR	= includes/Libft
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_FLAGS	= -lm

SRCS		= srcs/main.c \
			  srcs/init.c \
			  srcs/parser.c \
			  srcs/map_parser.c \
			  srcs/raycaster.c \
			  srcs/render.c

OBJS		= $(SRCS:.c=.o)

INC			= -I includes -I $(LIBFT_DIR)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(LIBFT_DIR) -lft -lmlx -L/usr/lib -lX11 -lm $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
