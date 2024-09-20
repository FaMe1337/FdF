# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: famendes <famendes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 15:56:51 by famendes          #+#    #+#              #
#    Updated: 2024/09/20 12:34:26 by famendes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS	= start.c fdf.c mlx.c controls.c points.c utils.c draw.c map_utils.c color.c

OBJS	:= $(SRCS:%.c=%.o)

NAME	= fdf

CC		= cc -Wall -Wextra -Werror -g
RM		= rm -f

CFLAGS 	= -Wall -Wextra -Werror #-fsanitize=address

all:		${NAME}

%.o:	%.c
		${CC} ${CFLAGS} -ILibft -Iprintf -Iminilibx -c $< -o $@

${NAME}:		${OBJS}
		@make -C Libft
		@make -C printf
		@make -C minilibx
		${CC} ${CFLAGS} $^ -LLibft -lft -Lprintf -lftprintf -Lminilibx -lmlx_Linux -lX11 -lm -lXext  -o ${NAME}

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
