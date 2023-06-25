/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:58:19 by khanhayf          #+#    #+#             */
/*   Updated: 2023/06/20 16:05:17 by khanhayf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	open_sem(t_ph *q)
{
	int	i;
	int	j;

	i = q->p->ph_num;
	j = 1;
	while (i-- > 0)
	{
		semaphore_open(q->l_eat, "/l_eat", j);
		semaphore_open(q->e_num, "/e_num", j);
		q = q->link;
		j++;
	}
	sem_unlink("/chopsticks");
	sem_unlink("/kill");
	q->p->kill = sem_open("/kill", O_CREAT, 0644, 0);
	q->p->chopsticks = sem_open("/chopsticks", O_CREAT, 0644, q->p->ph_num);
	sem_unlink("/print");
	q->p->print = sem_open("/print", O_CREAT, 0644, 1);
	sem_unlink("/nb");
	q->p->nb = sem_open("/nb", O_CREAT, 0644, 0);
	if ((q->p->kill == (sem_t *)-1) || (q->p->chopsticks == (sem_t *)-1)
		|| (q->p->print == (sem_t *)-1) || (q->p->nb == (sem_t *)-1))
		exit(1);
}

void	*dead(void *arg)
{
	t_ph	*q;

	q = (t_ph *)arg;
	while (1)
	{
		usleep(1000);
		sem_wait(q->l_eat);
		if ((gettime() - q->p->tv - q->l_meal) >= q->p->t2d)
		{
			sem_wait(q->p->print);
			printf("%ld\t%d\tdied\n", (gettime() - q->p->tv), q->id);
			sem_post(q->l_eat);
			sem_post(q->p->kill);
			exit(0);
		}
		sem_post(q->l_eat);
	}
}

void	th_creater(t_ph *q)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, dead, q) != 0)
		exit(0);
	if (pthread_detach(thread) != 0)
		exit(0);
}

void	routine(t_ph *q)
{
	th_creater(q);
	while (1)
	{
		sem_wait(q->p->chopsticks);
		print(q, (gettime() - q->p->tv), q->id, "has taken a fork");
		sem_wait(q->p->chopsticks);
		print(q, (gettime() - q->p->tv), q->id, "has taken a fork");
		print(q, (gettime() - q->p->tv), q->id, "is eating");
		sem_wait(q->l_eat);
		q->l_meal = (gettime() - q->p->tv);
		sem_post(q->l_eat);
		sem_wait(q->e_num);
		if (q->p->ac == 6 && q->eat_num-- > 0)
		{
			if (q->eat_num == 0)
				sem_post(q->p->nb);
		}
		sem_post(q->e_num);
		ft_usleep(q->p->t2e);
		sem_post(q->p->chopsticks);
		sem_post(q->p->chopsticks);
		print(q, (gettime() - q->p->tv), q->id, "is sleeping");
		ft_usleep(q->p->t2s);
		print(q, (gettime() - q->p->tv), q->id, "is thinking");
	}
}
