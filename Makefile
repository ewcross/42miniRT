# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecross <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 15:11:23 by ecross            #+#    #+#              #
#    Updated: 2020/02/12 15:29:38 by ecross           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = 	parser.c \
		parser_utils.c \
		view_scene.c

OBJS = ${SRCS:.c=.o}

LIBS = libft.a \
	   libgnl.a

RM = rm -f

GCC = gcc

CFLAGS = -Wall -Wextra -Werror

.c.o: ${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	ggm ${OBJS} ${LIBS}

all:		${NAME}

bonus:		all

clean:
	${RM} ${OBJS}

fclean:		clean
	${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re
