SRC		= main.c parsing.c
OBJ		= $(SRC:.c=.o)
CFLAGS	= -fsanitize=address -Wall -Wextra -g
CC=clang
LFLAGS	= -lmlx -lXext -lX11 
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
