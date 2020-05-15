# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecross <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 15:11:23 by ecross            #+#    #+#              #
#    Updated: 2020/05/15 10:39:59 by ecross           ###   ########.fr        #
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

LIBS = libft.a \
       libgnl.a \
       libmlx.a

RM = rm -f

GCC = gcc

GMM = gcc -framework OpenGL -framework AppKit

CFLAGS = -Wall -Wextra -Werror

.c.o: ${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	${GMM} -o ${NAME} ${OBJS} ${LIBS}

all:		${NAME}

clean:
	${RM} ${OBJS}

fclean:		clean
	${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re
