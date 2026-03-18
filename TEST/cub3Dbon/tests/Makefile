CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -DUNITY_INCLUDE_DOUBLE=1
INCLUDES = -I../includes -I../includes/Libft -I./unity

UNITY_DIR = unity
UNITY_SRC = $(UNITY_DIR)/unity.c

TEST_DIR = unit_tests
SRC_DIR = ../srcs

LIBFT_DIR = ../includes/Libft
LIBFT = $(LIBFT_DIR)/libft.a

all: test_utils

test_utils: $(TEST_DIR)/test_utils.c $(UNITY_SRC) $(SRC_DIR)/utils.c $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -L$(LIBFT_DIR) -lft -lm

# TODO: Add these tests when parser functions are available
# test_color_parser: $(TEST_DIR)/test_color_parser.c $(UNITY_SRC) $(SRC_DIR)/color_parser.c $(LIBFT)
# 	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -L$(LIBFT_DIR) -lft -lm

# test_texture_parser: $(TEST_DIR)/test_texture_parser.c $(UNITY_SRC) $(SRC_DIR)/texture_parser.c $(LIBFT)
# 	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -L$(LIBFT_DIR) -lft -lm

$(LIBFT):
	@make -C $(LIBFT_DIR)

run_tests: all
	@echo "=== Running Utils Tests ==="
	@./test_utils || echo "Utils tests failed"
	@echo ""
	@echo "All available tests completed!"

clean:
	rm -f test_utils test_color_parser test_texture_parser

fclean: clean

re: fclean all

.PHONY: all run_tests clean fclean re
