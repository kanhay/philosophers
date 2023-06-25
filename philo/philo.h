/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:49:41 by khanhayf          #+#    #+#             */
/*   Updated: 2023/06/20 14:43:59 by khanhayf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct arguments
{
	int				ph_num;
	int				t2d;
	int				t2e;
	int				t2s;
	int				e_times;
	long			tv;
	pthread_mutex_t	print;
	int				ac;
}	t_args;

typedef struct philo
{
	int				id;
	pthread_t		thread;
	t_args			*p;
	pthread_mutex_t	chopstick;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	e_num_mutex;
	long			l_meal;
	struct philo	*link;
	int				eat_num;
	int				pe_times;
}	t_ph;

typedef struct variables
{
	int		i;
	long	r;
	int		s;
	t_ph	*new;
	t_ph	*ptr;
}	t_var;

void	ft_error(void);
long	ft_atoi(const char *str);
int		check_args(char **av);
t_ph	*list(t_ph *q, t_args *p, int ph_num);
int		t_args_init(t_args *p, char **av, int ac);
int		mutex_init(t_ph *q, int ph_num);
int		th_create(t_ph *q);
void	*routine(void *arg);
long	gettime(void);
void	ft_usleep(int n);
int		print(t_ph	*q, int time, int id, char *s);
int		dead(t_ph	*q);

#endif