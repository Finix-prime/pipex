##

NAME = pipex
FLAGS = -Wall -Werror -Wextra
INCLUDE = get_next_line/libgl.a
SRCS = main.c split.c

all:
	@gcc -g $(FLAGS) $(INCLUDE) $(SRCS) -o $(NAME)

clean:
	@rm -rf a.out

fclean: clean
	@rm -rf $(NAME)

re: fclean all


#./pipex infile "grep -b" "wc -l" outfile
