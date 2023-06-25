/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:51:31 by khanhayf          #+#    #+#             */
/*   Updated: 2023/06/20 16:31:39 by khanhayf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	end(t_ph *q)
{
	int	i;
	int	j;

	if (sem_close(q->p->chopsticks) || sem_close(q->l_eat)
		|| sem_close(q->e_num) || sem_close(q->p->kill))
		exit(0);
	if (sem_post(q->p->nb))
		exit(0);
	if (sem_close(q->p->nb))
		exit(0);
	i = q->p->ph_num;
	j = 1;
	while (i-- > 0)
	{
		semaphore_unlink("l_eat", j);
		semaphore_unlink("e_num", j);
		j++;
		q = q->link;
	}
	if (sem_unlink("kill") || sem_unlink("chopsticks") || sem_unlink("nb"))
		exit(0);
	exit(0);
}

void	*done(void *q)
{
	t_ph	*philo;
	int		i;

	philo = q;
	i = 0;
	while (i < philo->p->ph_num)
	{
		if (sem_wait(philo->p->nb))
			exit(1);
		philo = philo->link;
		i++;
	}
	if (sem_wait(philo->p->print))
		exit(1);
	if (sem_post(philo->p->kill))
		exit(1);
	return (NULL);
}

void	finish(t_ph *philo)
{
	int			i;
	pthread_t	eat_nb;

	if (philo->p->ac == 6)
	{
		if (pthread_create(&eat_nb, NULL, done, philo) != 0)
			exit(0);
		if (pthread_detach(eat_nb) != 0)
			exit(0);
	}
	if (sem_wait(philo->p->kill) != 0)
		exit(0);
	i = 0;
	while (i < philo->p->ph_num)
	{
		kill(philo->pid, SIGINT);
		philo = philo->link;
		i++;
	}
	end(philo);
}

void	childs(t_ph *philo)
{
	int	i;

	philo->p->tv = gettime();
	i = 0;
	while (i++ < philo->p->ph_num)
	{
		philo->l_meal = 0;
		philo->pid = fork();
		if (philo->pid < 0)
			exit(0);
		if (philo->pid == 0)
			routine(philo);
		usleep(200);
		philo = philo->link;
	}
	finish(philo);
}

int	main(int ac, char **av)
{
	t_args	args;
	t_ph	*philo;

	philo = NULL;
	if (ac < 5 || ac > 6)
		ft_error();
	check_args(av);
	if (ft_atoi(av[1]) == 0)
		return (0);
	t_args_init(&args, av, ac);
	philo = list(philo, &args, args.ph_num);
	open_sem(philo);
	childs(philo);
	return (0);
}
