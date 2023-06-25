/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:30:38 by khanhayf          #+#    #+#             */
/*   Updated: 2023/06/20 15:41:26 by khanhayf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int n)
{
	long	start_t;

	start_t = gettime();
	while (gettime() <= (start_t + n))
		usleep(1000);
}

int	th_create(t_ph *q)
{
	int	i;

	q->p->tv = gettime();
	i = q->p->ph_num;
	while (i-- > 0)
	{
		q->l_meal = 0;
		if (q->p->ac == 6)
			q->eat_num = q->p->e_times;
		if (pthread_create(&q->thread, NULL, routine, q) != 0)
			return (1);
		if (pthread_detach(q->thread))
			return (1);
		usleep(100);
		q = q->link;
	}
	if (dead(q))
		return (1);
	return (0);
}

int	mutex_init(t_ph *q, int ph_num)
{
	while (ph_num-- > 0)
	{
		if ((pthread_mutex_init(&q->chopstick, NULL)) != 0)
			return (1);
		if (pthread_mutex_init(&q->eat_mutex, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&q->e_num_mutex, NULL) != 0)
			return (1);
		q = q->link;
	}
	return (0);
}

int	print(t_ph	*q, int time, int id, char *s)
{
	if (pthread_mutex_lock(&q->p->print))
		return (1);
	printf("%d\t%d\t%s\n", time, id, s);
	if (pthread_mutex_unlock(&q->p->print))
		return (1);
	return (0);
}
