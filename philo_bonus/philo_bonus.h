/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:53:53 by khanhayf          #+#    #+#             */
/*   Updated: 2023/06/20 12:05:26 by khanhayf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>
# include <pthread.h>

typedef struct arguments
{
	int				ph_num;
	int				t2d;
	int				t2e;
	int				t2s;
	int				e_times;
	long			tv;
	int				ac;
	sem_t			*print;
	sem_t			*kill;
	sem_t			*chopsticks;
	sem_t			*nb;
}	t_args;

typedef struct philo
{
	int				id;
	pid_t			pid;
	t_args			*p;
	long			l_meal;
	struct philo	*link;
	int				eat_num;
	sem_t			*l_eat;
	sem_t			*e_num;
}	t_ph;

typedef struct variables
{
	int		i;
	long	r;
	int		s;
	t_ph	*new;
	t_ph	*ptr;
}	t_var;

void	check_args(char **av);
int		t_args_init(t_args *p, char **av, int ac);
long	ft_atoi(const char *str);
int		ft_error(void);
t_ph	*list(t_ph *q, t_args *p, int ph_num);
long	gettime(void);
void	print(t_ph	*q, long time, int id, char *s);
void	ft_usleep(int n);
void	semaphore_open(sem_t *sem, char *s, int i);
char	*ft_strjoin(char *s1, char c);
void	semaphore_unlink(char *s, int i);
void	*dead(void *arg);
void	routine(t_ph *q);
void	open_sem(t_ph *q);

#endif 