# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 10:58:51 by sheiles           #+#    #+#              #
#    Updated: 2025/01/24 11:58:59 by sheiles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name
NAME = so_long

# Libraries and Paths
MLX = libmlx_Linux.a
LIBFT = libft.a

LFT_PATH = ../Libft/
MLX_PATH = ../minilibx-linux/
INCLUDES = ../include
SRCDIR = ../src/

# Source and Object Files
SRC = $(SRCDIR)main.c \
      $(SRCDIR)map_parser.c \
      $(SRCDIR)graphics.c \
      $(SRCDIR)input_handling.c \
      $(SRCDIR)game_logic.c \
      $(SRCDIR)error_handling.c \
      $(SRCDIR)utils.c
OBJ=$(notdir $(SRC:.c=.o))

# Compilation
CF = -Wall -Wextra -Werror
CC = gcc
MLX_CF = -lm -lbsd -lmlx -lXext -lX11
CFI = -I$(INCLUDES)
LEAKS = valgrind
LEAKS_FILE = valgrind-out.txt
LF = --leak-check=full \
     --show-leak-kinds=all \
     --track-origins=yes \
     --verbose \
     --log-file=$(LEAKS_FILE) \
     ./so_long maps/example_map.ber

# Common Commands
RM = rm -f

# Rules
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@printf "\n$(CY)Generating so_long executable...$(RC)\n"
	$(CC) $(CF) -o $(NAME) $(OBJ) -L $(LFT_PATH) -L $(MLX_PATH) -lft $(MLX_CF)
	mkdir objs
	mv $(OBJ) objs/
	@printf "$(GR)Done!$(RC)\n\n"

$(OBJ): $(SRC)
	@printf "\n$(CY)Compiling source files...$(RC)\n"
	$(CC) $(CF) -g -c -I ./includes/ $(SRC)
	@printf "$(GR)Objects ready!$(RC)\n\n"

$(MLX):
	@printf "\n$(CY)Generating MiniLibX...$(RC)\n"
	@make -C $(MLX_PATH)
	@printf "$(GR)MiniLibX created!$(RC)\n\n"

$(LIBFT):
	@printf "\n$(CY)Generating Libft...$(RC)\n"
	@make -C $(LFT_PATH)
	@printf "$(GR)Libft created!$(RC)\n\n"

bonus: all

re: fclean all

rebonus: fclean bonus

leaks: 
	$(LEAKS) $(LF)
	@printf "$(GR)Leaks log ready! Check valgrind-out.txt $(RC)\n\n"

cleanleaks: 
	$(RM) $(LEAKS_FILE)
	@printf "$(GR)Leaks log file deleted.$(RC)\n\n"

clean:
	@printf "\n$(YE)Cleaning all object files from libft...$(RC)\n"
	@make clean -C $(LFT_PATH)
	@printf "$(GR)Libft objects removed!$(RC)\n\n"
	$(RM) -rf $(OBJ) objs/

fclean: clean
	@printf "\n$(YE)Cleaning all additional objects and libraries...$(RC)\n"
	$(RM) -rf $(NAME) objs/
	@make fclean -C $(LFT_PATH)
	@printf "$(GR)All libraries removed!$(RC)\n\n"
	make cleanleaks

install: 
	sudo apt-get install gcc make xorg libxext-dev libbsd-dev -y
	@printf "$(GR)All dependencies ready!$(RC)\n\n"

.PHONY: clean fclean re rebonus all bonus

# Colors
GR = \033[32;1m
RE = \033[31;1m
YE = \033[33;1m
CY = \033[36;1m
RC = \033[0m
