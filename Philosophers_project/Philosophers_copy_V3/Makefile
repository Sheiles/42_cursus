
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = main.c init.c philosopher.c monitor.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

debug: $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=address -fsanitize=leak -o $(NAME) $(OBJS) -lpthread

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
