# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 14:54:30 by taewonki          #+#    #+#              #
#    Updated: 2025/09/08 14:55:21 by taewonki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================== #
#                                 VARIABLES                                      #
# ============================================================================== #

NAME 		= philo

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g -pthread

SRCS 		= 	check.c \
				get_time.c \
				init.c \
				main.c \
				monitor.c \
				mutex_utils.c \
				routine.c \
				routine_even.c \
				routine_odd.c \
				simulation.c \
				util.c

# 소스 파일 목록으로부터 오브젝트 파일 목록 (.o)을 자동으로 생성합니다.
# e.g., main.c -> main.o
OBJS		= $(SRCS:.c=.o)

# 삭제 명령어
RM			= rm -f

# ============================================================================== #
#                                   RULES                                        #
# ============================================================================== #

# 기본 규칙: 'make' 또는 'make all' 입력 시 $(NAME)을 빌드합니다.
all:		$(NAME)

# 실행 파일($(NAME)) 생성 규칙
# $(OBJS) 파일들이 모두 준비되면, 이들을 링크하여 최종 실행 파일을 생성합니다.
$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# C 소스 파일(.c)을 오브젝트 파일(.o)로 컴파일하는 일반 규칙
# $<: 규칙의 첫 번째 전제조건 (e.g., main.c)
# $@: 규칙의 대상 (e.g., main.o)
# -c: 소스 코드를 컴파일만 하고 링크는 하지 말라는 옵션입니다.
# philo.h가 변경되면 모든 .c 파일이 다시 컴파일됩니다.
%.o: %.c philo.h
	$(CC) $(CFLAGS) -c -o $@ $<

# 오브젝트 파일들을 삭제하는 규칙
clean:
	$(RM) $(OBJS)

# 오브젝트 파일과 실행 파일을 모두 삭제하는 규칙
fclean:		clean
	$(RM) $(NAME)

# 전체 재빌드 규칙: 'make fclean' 실행 후 'make all'을 실행합니다.
re:			fclean all

# 가짜(phony) 타겟: all, clean, fclean, re는 실제 파일 이름이 아니므로
# make가 혼동하지 않도록 .PHONY로 선언해주는 것이 좋습니다.
.PHONY:		all clean fclean re
