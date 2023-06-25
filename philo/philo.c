/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:48:58 by khanhayf          #+#    #+#             */
/*   Updated: 2023/06/20 16:31:47 by khanhayf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_ph	*q;

	q = (t_ph *)arg;
	while (1)
	{
		pthread_mutex_lock(&q->chopstick);
		print(q, (gettime() - q->p->tv), q->id, "has taken a fork");
		pthread_mutex_lock(&q->link->chopstick);
		print(q, (gettime() - q->p->tv), q->id, "has taken a fork");
		print(q, (gettime() - q->p->tv), q->id, "is eating");
		pthread_mutex_lock(&q->eat_mutex);
		q->l_meal = (gettime() - q->p->tv);
		pthread_mutex_unlock(&q->eat_mutex);
		pthread_mutex_lock(&q->e_num_mutex);
		if (q->p->ac == 6 && q->eat_num > 0)
			q->eat_num--;
		pthread_mutex_unlock(&q->e_num_mutex);
		ft_usleep(q->p->t2e);
		pthread_mutex_unlock(&q->chopstick);
		pthread_mutex_unlock(&q->link->chopstick);
		print(q, (gettime() - q->p->tv), q->id, "is sleeping");
		ft_usleep(q->p->t2s);
		print(q, (gettime() - q->p->tv), q->id, "is thinking");
	}
}

int	ph_eatingtimes(t_ph *q)
{
	int		i;

	i = q->p->ph_num;
	while (i > 0)
	{
		if (pthread_mutex_lock(&q->e_num_mutex))
			return (1);
		if (q->eat_num != 0)
		{
			if (pthread_mutex_unlock(&q->e_num_mutex))
				return (1);
			break ;
		}
		if (pthread_mutex_unlock(&q->e_num_mutex))
			return (1);
		i--;
		q = q->link;
	}
	if (i == 0)
		return (2);
	return (0);
}

int	dead(t_ph	*q)
{
	while (1)
	{
		if (q->p->ac == 6)
		{
			if (ph_eatingtimes(q) == 2)
				return (0);
		}
		if (pthread_mutex_lock(&q->eat_mutex))
			return (1);
		if (((gettime() - q->p->tv) - q->l_meal) >= q->p->t2d)
		{
			if (pthread_mutex_lock(&q->p->print))
				return (1);
			printf("%ld\t%d\tdied\n", (gettime() - q->p->tv), q->id);
			if (pthread_mutex_unlock(&q->eat_mutex))
				return (1);
			return (0);
		}
		if (pthread_mutex_unlock(&q->eat_mutex))
			return (1);
		q = q->link;
	}
}

int	end(t_ph	*q)
{
	while (q->p->ph_num-- > 0)
	{
		if (pthread_mutex_destroy(&q->chopstick))
			return (1);
		if (pthread_mutex_destroy(&q->eat_mutex))
			return (1);
		if (pthread_mutex_destroy(&q->e_num_mutex))
			return (1);
		q = q->link;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_args	p;
	t_ph	*q;

	q = NULL;
	if (ac < 5 || ac > 6)
	{
		ft_error();
		return (1);
	}
	if (check_args(av))
		return (1);
	else if ((ft_atoi(av[1])) == 0)
		return (0);
	if (t_args_init(&p, av, ac))
		return (0);
	q = list(q, &p, p.ph_num);
	if (mutex_init(q, p.ph_num))
		return (1);
	if (th_create(q))
		return (1);
	if (end(q))
		return (1);
	return (0);
}
