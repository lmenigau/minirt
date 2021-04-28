SRC		= main.c parsing.c storage.c down.c vec.c screen.c render.c
OBJ		= $(SRC:.c=.o)
CFLAGS	= -g -Wall -Wextra
LFLAGS	=  -lmlx -lXext -lX11
LDFLAGS	= -L/Users/lomeniga/mp/lib -lX11 -lXext -L minilibx-linux 
NAME	= Minirt
CFLAGS += -I minilibx-linux
ifeq  '$(shell ar V 2>/dev/null | head -c 3)' 'GNU'
	ARFLAGS	= Ur
endif

$(NAME) : $(OBJ) 
	$(CC)  -o $(NAME) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LFLAGS) 

.PHONY	: re clean fclean all

fclean	: clean
		$(RM) $(NAME)

clean	:
		$(RM) *.o

re		: fclean  all

all		: $(NAME)
