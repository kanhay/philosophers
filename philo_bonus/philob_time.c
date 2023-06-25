/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philob_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:58:06 by khanhayf          #+#    #+#             */
/*   Updated: 2023/06/19 21:21:16 by khanhayf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit (1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int n)
{
	long	start_t;

	start_t = gettime();
	while (gettime() <= (start_t + n))
		usleep(1000);
}
