SRC		= main.c
OBJ		= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -g -I.
CC=clang
LFLAGS	= -lmlx -lXext -lX11
LDFLAGS	= -L minilibx-linux 
NAME	= Minirt
ifeq  '$(shell ar V 2>/dev/null | head -c 3)' 'GNU'
	ARFLAGS	= Ur
endif

$(NAME) : $(OBJ) 
	$(CC) $(OBJ) -lmlx -lXext -lX11

.PHONY	: re clean fclean all

fclean	: clean
		$(RM) $(NAME)

clean	:
		$(RM) *.o

re		: fclean  all

all		: $(NAME)
