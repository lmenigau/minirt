SRC		= main.c
OBJ		= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -g 

NAME	= Cub3d
ifeq  '$(shell ar V 2>/dev/null | head -c 3)' 'GNU'
	ARFLAGS	= Ur
endif

$(NAME) : $(OBJ) 
	$(CC) $(OBJ) libmlx.dylib

.PHONY	: re clean fclean all

fclean	: clean
		$(RM) $(NAME)

clean	:
		$(RM) *.o

re		: fclean  all

all		: $(NAME)
