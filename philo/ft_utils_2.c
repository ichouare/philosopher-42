/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:55:52 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/04 12:19:40 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_decal(int id)
{
	int	j;

	j = 0;
	if (id % 2)
	{
		while (j < 1000)
		{
			usleep (1);
			j++;
		}
	}
}

t_philosopher	*t_allocate_thread(int n)
{
	t_philosopher	*vars;

	vars = malloc (sizeof(t_philosopher) * n);
	if (vars == NULL)
		return (0);
	return (vars);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	ft_clock(t_philosopher	*p)
{
	struct timeval	timestamp;

	gettimeofday (&timestamp, NULL);
	pthread_mutex_lock(p->time);
	p->last_eat = (timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000);
	pthread_mutex_unlock(p->time);
}

void	init_thread(t_philosopher *vars, char **av, int ag)
{
	vars->nthreads = ft_atoi(av[1]);
	vars->die = ft_atoi(av[2]);
	vars->eat = ft_atoi(av[3]);
	vars->sleep = ft_atoi(av[4]);
	vars->number_eat = 0;
	if (ag == 6)
		vars->count_eat = ft_atoi(av[5]);
}
