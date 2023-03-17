# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 11:53:12 by ichouare          #+#    #+#              #
#    Updated: 2023/03/11 20:45:25 by ichouare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc 

FLAG = -Wall -Wextra  -Werror 

HEADER = ./philoBonus.h


SRCS =   main.c ft_atoi.c ft_strlen.c Bonus_utils.c  Bonus_help.c \


OBJS = $(SRCS:.c=.o)


all: $(NAME)


$(NAME): $(OBJS) 
	$(CC) $(FLAG)  $^ -o $@
 
	
%.o : %.c  $(HEADER)
	$(CC) $(FLAG)  -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all 