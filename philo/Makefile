# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/22 18:55:37 by khanhayf          #+#    #+#              #
#    Updated: 2023/06/20 16:25:36 by khanhayf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEAD = philo.h

SRC = philo.c parsing.c philo_utils.c

OBJ = philo.o parsing.o philo_utils.o

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
