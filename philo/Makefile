# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 14:47:33 by ichouare          #+#    #+#              #
#    Updated: 2023/04/04 11:53:50 by ichouare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc 

FLAG = -Wall -Wextra  -Werror 

HEADER = ./philosopher.h


SRCS =   main.c ft_atoi.c   ft_utils.c ft_utils_1.c ft_utils_2.c ft_utils_3.c\


OBJS = $(SRCS:.c=.o)


all: $(NAME)

Bonus :  $(NAMEB)

$(NAME): $(OBJS) 
	$(CC) $(FLAG)  $^ -o $@
 
	
%.o : %.c  $(HEADER)
	$(CC) $(FLAG)  -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all 