
SOURCE_DIR	= srcs/
SOURCES		= main.c utils.c bsp.c

OBJ_DIR		= objs/
OBJS		= ${SOURCES:.c=.o}
OBJS		:= $(addprefix ${OBJ_DIR}, ${OBJS})

NAME	= wallpaper

MLX_DIR	= mlx
CC	= gcc #-g3 -fsanitize=address
CFLAGS	= -Wall -Wextra -Werror -Imlx
RM	= rm -f
AR	= ar rc

${OBJ_DIR}%.o: ${SOURCE_DIR}%.c
		mkdir -p ${OBJ_DIR}
		${CC} ${CFLAGS} -Imlx -c $< -o $@

all:	${NAME}

${NAME}:	${OBJS}
		@echo "\033[95m\nCompiling mlx...\033[0m"
		make -C ${MLX_DIR}
		@echo "\033[95m\nGenerating wallpaper file...\033[0m"
		${CC} ${OBJS} -Lmlx -lmlx -lXext -lX11 -lm -o $@

clean:
		@echo "\033[91mclean mlx\033[0m"
		make -C ${MLX_DIR} clean
		${RM} ${OBJS}
		rm -rf ${OBJ_DIR}

fclean:		clean
		${RM} ${NAME}
		${RM} libmlx.dylib

re:		fclean all

.PHONY:	all clean fclean re

