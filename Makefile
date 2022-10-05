SRC		= main.c parsing.c storage.c down.c vec.c screen.c render.c light.c
LFLAGS	=  -lmlx -lXext -lX11 -lm
LDFLAGS	= -L minilibx-linux
NAME	= miniRT
OPTFLAGS = -march=native -Ofast -flto=full
CFLAGS	:= -g -Wall -Wextra -Werror $(OPTFLAGS) $(DEBUG) 
CPPFLAGS += -I minilibx-linux
OBJ		:= $(addprefix obj/, $(SRC:.c=.o))
CC		= cc
DEP := $(addprefix dep/, $(SRC:.c=.d))

ERRORFILE	:= $(addprefix err/, $(addsuffix .err, $(SRC) $(HEADER)))

$(NAME) : $(OBJ) 
	$(CC)  -o $(NAME) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LFLAGS)

$(OBJ)	: obj/%.o : %.c dep/%.d | obj
	$(CC) $(CPPFLAGS) $(CFLAGS) -c  $< -o $@

$(DEP)	: dep/%.d: %.c | dep
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

dep:
	mkdir dep

include $(DEP)

$(OBJ)	: | obj

obj		:
	mkdir obj

all		: $(NAME)

fclean	: clean
		$(RM) $(NAME)

clean	:
		$(RM) -rf obj
		$(RM) -rf dep

re		: fclean
	$(MAKE)

norm	: errors.err

$(ERRORFILE) : err/%.err : %
	-norminette $< > $@

errors.err: $(ERRORFILE)
	cat $^ > errors.err | awk '! /OK/ {print}' | touch $@

.PHONY	: re clean fclean all norm
