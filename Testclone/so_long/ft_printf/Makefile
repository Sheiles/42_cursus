NAME = libftprintf.a

INCLUDE = .

CFLAGS = -Wall -Wextra -Werror

CC = cc

RM = rm -rf

AR = ar rcs

SRC_FUNC = 	ft_percentage \
			ft_print_char \
			ft_print_hex_lower \
			ft_print_hex_upper \
			ft_print_numbers \
			ft_print_pointer \
			ft_print_string \
			ft_printf \
			ft_print_unsigned_int \
			ft_print_signed_int \

SRC = $(addsuffix .c, $(SRC_FUNC))

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
