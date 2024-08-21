# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: famendes <famendes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 15:56:51 by famendes          #+#    #+#              #
#    Updated: 2024/08/21 18:49:53 by famendes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS	= start.c fdf.c

OBJS	:= $(SRCS:%.c=%.o)

NAME	= fdf

CC		= cc -Wall -Wextra -Werror -g
RM		= rm -f

CFLAGS 	= -Wall -Wextra -Werror #-fsanitize=address

all:		${NAME}

%.o:	%.c
		${CC} ${CFLAGS} -ILibft -Iprintf -I./minilibx -c $< -o $@

${NAME}:		${OBJS}
		@make -C Libft
		@make -C printf
		@make -C minilibx
		${CC} ${CFLAGS} $^ -LLibft -lft -Lprintf -lftprintf -L./minilibx -lmlx  -o ${NAME}

libft:
		make -C Libft

printf:
		make -C printf

minilibx:
		make -C minilibx

clean:
			make clean -C Libft
			make clean -C printf
			make clean -C minilibx
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		Libft printf