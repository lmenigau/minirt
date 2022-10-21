SRC		= down.c            \
		  libft.c           \
		  light.c           \
		  main.c            \
		  parse_camcyl.c    \
		  parse_light.c     \
		  parse_num.c       \
		  parse_object.c    \
		  parse_start.c     \
		  parsing.c         \
		  planes.c          \
		  remove.c          \
		  render.c          \
		  screen.c          \
		  storage.c         \
		  sphere.c          \
		  vec.c             \
		  transform.c       \
		  arithmv3.c        \
		  arithmv4.c		\
		  mat.c             \
		  mat_inv.c         \
		  mat_inv_utils.c   \
		  cylinders.c       \
		  cylinders_inter.c \

OBJ		:= $(addprefix obj/, $(SRC:.c=.o))
DEP := $(addprefix dep/, $(SRC:.c=.d))
ERRORFILE	:= $(addprefix err/, $(addsuffix .err, $(SRC) $(HEADER)))

MLX_DIR = ./minilibx-linux
MLX = libmlx_Linux.a
MLX_L = ${MLX:lib%.a=%}

NAME	= miniRT

CFLAGS	:= $(DEBUG) -Ofast -march=native -flto -g -Wall -Wextra -Werror
CPPFLAGS += -I ${MLX_DIR}
LFLAGS	=  -l${MLX_L} -lXext -lX11 -lm
LDFLAGS	= -L ${MLX_DIR}

CC		= clang

$(NAME) : ${MLX_DIR}/${MLX} $(OBJ)
	$(CC)  -o $(NAME) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LFLAGS)

${MLX_DIR}/${MLX}:
	make -C ${MLX_DIR}

$(OBJ)	: obj/%.o : %.c dep/%.d | dep
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

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
	make -C ${MLX_DIR} clean

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
