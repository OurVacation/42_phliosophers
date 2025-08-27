# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/26 16:26:40 by taewonki          #+#    #+#              #
#    Updated: 2025/08/27 11:32:44 by taewonki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -Iincludes
NAME = philo
SRCS = srcs/check.c srcs/get_time.c srcs/init.c srcs/main.c srcs/monitor.c \
	srcs/mutex_utils.c srcs/routine.c srcs/simulation.c srcs/util.c
OBJS = $(SRCS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
