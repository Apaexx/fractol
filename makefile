
SRC = juliamandel.c fract.c init.c input.c output.c

NAME = lib.a

all:	$(NAME)

$(NAME) : $(SRC:.c=.o)
	@gcc -Wall -Werror -Wextra -O3 -c $(SRC)
	@gcc -g -Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit $(SRC:.c=.o) -o fractol -O3

clean:
	@rm -f $(SRC:.c=.o)

fclean:	clean
	@rm -f fractol

re:		fclean all