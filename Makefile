# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 15:01:28 by raphox            #+#    #+#              #
#    Updated: 2025/02/06 18:17:30 by rafaria          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

SRCS			=	tools.c main.c check_args.c dinner_start.c

OBJS			=	${SRCS:.c=.o}

CC			=	cc

# CFLAGS		=	-Wall -Werror -Wextra -g3

all			:	${NAME}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean			:
	rm -rf ${OBJS}

fclean			:	clean
	rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re