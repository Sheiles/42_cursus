
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sheiles <sheiles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/15 00:00:00 by sheiles           #+#    #+#              #
#    Updated: 2025/08/15 00:00:00 by sheiles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
SRCS		= main.c args.c init.c philosopher.c actions.c \
			  monitor.c threads.c utils.c
OBJS		= $(SRCS:.c=.o)
RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: CFLAGS += -g -fsanitize=address -fsanitize=leak
debug: re

.PHONY: all clean fclean re debug
