/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:22:32 by khanhayf          #+#    #+#             */
/*   Updated: 2023/06/20 16:22:32 by khanhayf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(void)
{
	write (2, "Error\n", 6);
	return ;
}

long	ft_atoi(const char *str)
{
	t_var	p;

	p.i = 0;
	p.s = 1;
	p.r = 0;
	if (str[p.i] == '\0')
		return (-1);
	while (str[p.i] == ' ' || (str[p.i] >= '\t' && str[p.i] <= '\r'))
		p.i++;
	if (str[p.i] == '\0')
		return (-1);
	if (str[p.i] == '+' || str[p.i] == '-')
	{
		if (str[p.i] == '-')
			p.s = -1;
		p.i++;
	}
	while (str[p.i] && str[p.i] >= '0' && str[p.i] <= '9')
		p.r = (p.r * 10) + (str[p.i++] - 48);
	while (str[p.i] && str[p.i] == ' ')
		p.i++;
	if (str[p.i])
		return (-1);
	return (p.r * p.s);
}

int	check_args(char **av)
{
	int		i;
	long	nb;

	i = 1;
	nb = 0;
	while (av[i])
	{
		nb = ft_atoi(av[i]);
		if (nb < 0 || nb > 2147483647)
		{
			ft_error();
			return (1);
		}
		i++;
	}
	return (0);
}

t_ph	*list(t_ph *q, t_args *p, int ph_num)
{
	t_var	pt;
	int		i;

	i = 1;
	while (ph_num-- > 0)
	{
		pt.new = malloc(sizeof(t_ph));
		if (!pt.new)
			return (NULL);
		pt.new->id = i++;
		pt.new->p = p;
		if (q == NULL)
		{
			q = pt.new;
			pt.ptr = pt.new;
		}
		else
		{
			pt.ptr->link = pt.new;
			pt.ptr = pt.new;
		}
	}
	pt.ptr->link = q;
	return (q);
}

int	t_args_init(t_args *p, char **av, int ac)
{
	p->ac = ac;
	p->ph_num = ft_atoi(av[1]);
	p->t2d = ft_atoi(av[2]);
	p->t2e = ft_atoi(av[3]);
	p->t2s = ft_atoi(av[4]);
	if (p->ac == 6)
	{
		p->e_times = ft_atoi(av[5]);
		if (p->e_times == 0)
			return (1);
	}
	if (pthread_mutex_init(&p->print, NULL))
		return (1);
	return (0);
}
