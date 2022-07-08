##

NAME = pipex
FLAGS = -Wall -Werror -Wextra
INCLUDE = get_next_line/libgl.a
SRCS = main.c split.c

all:
	@gcc $(FLAGS) $(INCLUDE) $(SRCS) -o $(NAME)
