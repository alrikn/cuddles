##
## EPITECH PROJECT, 2024
## My_printf
## File description:
## Makefile
##

NAME = libcuddle.a
TEST_BIN = unit_tests

SRC = $(shell find src -name '*.c')

TEST_SRC = $(SRC) \
	./unit_tests/unit_test_minishell.c

CC = gcc
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -g
INCLUDE_PATH = ./include/
LDFLAGS = -I$(INCLUDE_PATH)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)

$(LIB_NAME): $(OBJ)
	ar -rc $(LIB_NAME) $(OBJ)

$(TEST_BIN):
	$(CC) $(CFLAGS) -o $(TEST_BIN) $(TEST_SRC) $(TEST_LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ)
	rm -f *.gc*

fclean: clean
	rm -f $(LIB_NAME)
	rm -f $(NAME)
	rm -f $(TEST_BIN)

re: fclean $(LIB_NAME) $(NAME)

coverage: tests_run
	gcovr -r .
	gcovr -r . --branches

.PHONY: all re compile coverage fclean clean tester
