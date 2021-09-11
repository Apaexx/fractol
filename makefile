SRC = fract.c bool_checks.c mlx_dependencies.c

BONUS = $(SRC)

NAME = lib.a

all:	$(NAME)

$(NAME) : $(SRC:.c=.o)
	@gcc -Wall -Werror -Wextra -c $(SRC)
	@ar -rc  lib.a $(SRC:.c=.o)
	@ranlib lib.a
	@gcc -g -Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit lib.a -o fractol

bonus:
	@gcc -Wall -Werror -Wextra -c $(SRC) $(BONUS)
	@ar -rc  lib.a $(SRC:.c=.o)
	@ranlib lib.a

clean:
	rm -f $(SRC:.c=.o) $(BONUS:.c=.o) 

fclean:	clean
	rm -f fractol

re:		fclean all