# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecross <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 15:11:23 by ecross            #+#    #+#              #
#    Updated: 2020/02/12 16:33:42 by ecross           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

SRCS = 	parser.c \
		parser_utils.c \
		view_scene.c

OBJS = ${SRCS:.c=.o}

LIBS = libft.a \
	   libgnl.a

RM = rm -f

GMM = gcc libmlx.a -framework OpenGL -framework AppKit

CFLAGS = -Wall -Wextra -Werror

.c.o: ${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} clean
	${GMM} ${OBJS} ${LIBS}

all:		${NAME}

bonus:		all

clean:
	${RM} ${OBJS}

fclean:		clean
	${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re
