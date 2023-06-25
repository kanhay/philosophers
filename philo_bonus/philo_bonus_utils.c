/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:19:04 by khanhayf          #+#    #+#             */
/*   Updated: 2023/06/19 16:58:53 by khanhayf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	semaphore_open(sem_t *sem, char *s, int i)
{
	s = ft_strjoin(s, i + 48);
	sem = sem_open(s, O_CREAT, 0644, 1);
	if (sem == (sem_t *)-1)
		exit (1);
	free (s);
}

void	semaphore_unlink(char *s, int i)
{
	s = ft_strjoin(s, i + 48);
	if (sem_unlink(s))
		exit (1);
	free (s);
}

void	print(t_ph *q, long time, int id, char *s)
{
	if (sem_wait(q->p->print))
		exit (1);
	printf("%ld\t%d\t%s\n", time, id, s);
	if (sem_post(q->p->print))
		exit (1);
}

char	*ft_strjoin(char *s1, char c)
{
	int		i;
	char	*p;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	p = (char *)malloc(sizeof(char) * (i + 2));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i++] = c;
	p[i] = '\0';
	return (p);
}
