# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/10 12:55:23 by sheiles           #+#    #+#              #
#    Updated: 2024/12/24 09:33:36 by sheiles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SERVER = server
CLIENT = client

SERVER_SRC = server.c
CLIENT_SRC = client.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/Libft.a

all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(SERVER): $(SERVER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJ) -L$(LIBFT_DIR) -lft

$(CLIENT): $(CLIENT_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ) -L$(LIBFT_DIR) -lft

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(SERVER) $(CLIENT)
	make fclean -C $(LIBFT_DIR)

re: fclean all
