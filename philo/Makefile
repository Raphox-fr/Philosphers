# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 15:01:28 by raphox            #+#    #+#              #
#    Updated: 2025/03/04 17:11:23 by rafaria          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

SRCS			=	tools.c main.c check_args.c dinner_start.c time.c init.c forks.c monitor.c

OBJS			=	${SRCS:.c=.o}

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -fsanitize=thread

all			:	${NAME}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean			:
	rm -rf ${OBJS}

fclean			:	clean
	rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re

# -Wall -Werror -Wextra -g3