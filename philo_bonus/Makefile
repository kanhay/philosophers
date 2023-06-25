# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/04 19:50:12 by khanhayf          #+#    #+#              #
#    Updated: 2023/06/20 11:50:05 by khanhayf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

HEAD = philo_bonus.h

SRC = philo_bonus.c parsing_bonus.c philo_bonus_utils.c philob_time.c routine.c

OBJ = philo_bonus.o parsing_bonus.o philo_bonus_utils.o philob_time.o routine.o

CC = cc

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) 

%.o : %.c $(HEAD)
	$(CC) $(FLAGS) -c $<

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
