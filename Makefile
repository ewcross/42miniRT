# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecross <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 15:11:23 by ecross            #+#    #+#              #
#    Updated: 2020/05/25 12:48:12 by ecross           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRCS = 	bmp_1.c \
	bmp_2.c \
	free_funcs_1.c \
	free_funcs_2.c \
	maths_funcs_1.c \
	maths_funcs_2.c \
	obj_intercepts_1.c \
	obj_intercepts_2.c \
	obj_intercepts_3.c \
	obj_normals.c \
	parser_1.c \
	parser_2.c \
	parser_3.c \
	parser_4.c \
	parser_5.c \
	parser_6.c \
	parser_7.c \
	parser_8.c \
	sq_utils.c \
	struct_utils_1.c \
	struct_utils_2.c \
	view_scene_1.c \
	view_scene_2.c \
	view_scene_3.c \
	view_scene_4.c \
	view_scene_5.c \
	window_1.c \
	window_2.c

OBJS = ${SRCS:.c=.o}

OS = $(shell uname)

LIBFT = libft/libft.a
LIBGNL = libgnl/libgnl.a
ifeq ($(OS), Darwin)
LIBMLX = minilibx_mac/libmlx_mac.a	#need to check if the libmlx.a in the minilibx_linux folder works on mac	
else
LIBMLX = minilibx_linux/libmlx_Linux.a
endif

INC = -I./includes/ \
      -I./libft/ \
      -I./libgnl/ \
      -I./minilibx_linux/	#also check if the mlx.h in this folder works on mac

LIBS = libft/libft.a \
       libgnl/libgnl.a \

ifeq ($(OS), Darwin)
SRCS += r_func_mac.c free_img_list_mac.c
LIBS += minilibx_mac/libmlx_mac.a
else
SRCS += r_func_linux.c free_img_list_linux.c
LIBS += minilibx_linux/libmlx_Linux.a
endif

RM = rm -f

GCC = gcc

CFLAGS = -Wall -Wextra -Werror

G_MACOS = -framework OpenGL -framework AppKit
G_UBUNTU = -lm -lbsd -lX11 -lXext

%.o:		%.c
	${GCC} ${CFLAGS} ${INC} -c $< -o $@

all:	${LIBFT} ${LIBGNL} ${LIBMLX} ${NAME}

${LIBFT}:
	cd libft/ && ${MAKE}

${LIBGNL}:
	cd libgnl/ && ${MAKE}

${LIBMLX}:
ifeq ($(OS), Linux)
	cd minilibx_linux/ && ${MAKE}
endif

${NAME}:	${OBJS}
ifeq ($(OS), Darwin)
	${GCC} -o ${NAME} ${OBJS} ${LIBS} ${G_MACOS}
	@echo "\033[1;32m***Compiled and linked successfully***"
	@echo "\033[1;33m***Warning: screen resizing doesn't work on mac,"
	@echo "default values in includes/header.h will be used***"
else ifeq ($(OS), Linux)
	${GCC} -o ${NAME} ${OBJS} ${LIBS} ${G_UBUNTU}
	@echo "\033[1;32m***Compiled and linked successfully***"
else
	@echo "\033[1;31m***No linking rule for this OS***"
endif

clean:
	${RM} ${OBJS}
	${RM} libft/*.o
	${RM} libgnl/*.o
ifeq ($(OS), Linux)
	${RM} minilibx_linux/*.o
endif

fclean:		clean
	${RM} ${NAME}
	${RM} ${LIBFT}
	${RM} ${LIBGNL}
ifeq ($(OS), Linux)
	${RM} ${LIBMLX}
	${RM} minilibx_linux/libmlx.a
endif

re:		fclean all

.PHONY:		all clean fclean re
