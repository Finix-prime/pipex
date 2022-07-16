##

NAME = pipex
FLAGS = -Wall -Werror -Wextra
INCLUDE = get_next_line/libgl.a
SRCS = main.c split.c utils1.c

all:
	@gcc -g $(FLAGS) $(INCLUDE) $(SRCS) -o $(NAME)
	@touch outfile

clean:
	@rm -rf a.out
	@rm -rf *.dSYM

fclean: clean
	@rm -rf $(NAME)
	@rm -rf outfile

norm:
	@norminette -R CheckForbiddenSourceHeader

re: fclean all

