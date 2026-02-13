# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/12 00:00:00 by sheiles           #+#    #+#              #
#    Updated: 2026/02/12 00:00:00 by sheiles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I./includes -I./includes/Libft -I./mlx

SRCS_DIR	= srcs
OBJS_DIR	= objs

SRCS		= main.c init.c parser.c color_parser.c texture_parser.c \
			  map_parser.c raycaster.c render.c events.c utils.c

OBJS		= $(SRCS:%.c=$(OBJS_DIR)/%.o)

LIBFT_DIR	= includes/Libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= mlx
MLX			= $(MLX_DIR)/libmlx.a

UNAME_S		:= $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif
ifeq ($(UNAME_S),Darwin)
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif
ifeq ($(findstring CYGWIN,$(UNAME_S)),CYGWIN)
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

# Colors for output
GREEN		= \033[0;32m
BLUE		= \033[0;34m
RED			= \033[0;31m
YELLOW		= \033[0;33m
RESET		= \033[0m

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✅ Build complete!$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@echo "$(BLUE)🔨 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)📚 Building libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(MLX):
	@echo "$(YELLOW)🎨 Building MLX...$(RESET)"
	@make -C $(MLX_DIR)

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)🗑️  Removing executables...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

debug: CFLAGS += -g3 -fsanitize=address
debug: re

norm:
	@echo "$(BLUE)📋 Checking norminette (excluding MLX)...$(RESET)"
	@norminette $(SRCS_DIR) includes/*.h $(LIBFT_DIR) || true

norm_strict:
	@echo "$(BLUE)📋 Strict norminette check...$(RESET)"
	@norminette $(SRCS_DIR) includes/*.h $(LIBFT_DIR)

run: all
	@echo "$(GREEN)🚀 Running $(NAME)...$(RESET)"
	@./$(NAME) maps/test.cub

.PHONY: all clean fclean re debug norm norm_strict run
