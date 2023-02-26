/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:54:04 by ichouare          #+#    #+#             */
/*   Updated: 2023/02/26 17:38:06 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

int	ft_checkparms(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc < 5 || argc > 6)
		return (0);
	while (i < argc)
	{
		j = 0;
		if (ft_strlen(argv[i]) == 1)
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				i++;
			else
				return (0);
		}
		else
		{
			j = 0;
			if (argv[i][j] == '+' || (argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				j++;
				while (argv[i][j])
				{
					if (argv[i][j] >= '0' && argv[i][j] <= '9')
						j++;
					else
						return (0);
				}
			}
			else
				return (0);
			i++;
		}
	}
	return (1);
}

void	*test(void *vars)
{
	t_philosopher	*p;
	struct timeval	timestamp;
	long			time;
	int				j;

	p = (t_philosopher *)vars;
	time = p->begin_time;
	if (p->id % 2)
	{
		j = 0;
		while (j < 100)
		{
			usleep (1);
			j++;
		}
	}
	while (1)
	{
		pthread_mutex_lock (&p->mutex[p->id]);
		printmsg("%ld ms take the %d first fork \n", get_time(p), (p->id + 1));
		pthread_mutex_lock (&p->mutex[(p->id + 1) % p->nthreads]);
		printmsg("%ld ms take the %d second fork \n", get_time(p), (p->id + 1));
		gettimeofday (&timestamp, NULL);
		p->last_eat = (timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000);
		ft_eat(vars, time);
		pthread_mutex_unlock (&p->mutex[p->id]);
		pthread_mutex_unlock (&p->mutex[(p->id + 1) % p->nthreads]);
		ft_sleep(vars, time);
		printmsg("%lu ms %d  is thinking\n", get_time(p), (p->id + 1));
	}
	return (NULL);
}

int	ft_die(t_philosopher *tvars)
{
	struct timeval	tv;
	long			currenttime;
	long			time;

	gettimeofday (&tv, NULL);
	currenttime = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	time = currenttime - tvars->last_eat;
	if (time > tvars->die)
	{
		printmsg("%lu ms %d died",
			currenttime - tvars->begin_time, (tvars->id + 1));
		return (1);
	}
	return (0);
}

int	ft_sleep(t_philosopher *tvars, long timetamps)
{
	struct timeval	tv;
	struct timeval	timesleep;
	long			time;
	long			ntime;
	long			time_sleep;

	gettimeofday(&timesleep, NULL);
	time_sleep = (timesleep.tv_sec * 1000) + (timesleep.tv_usec / 1000);
	time = 0;
	printmsg("%lu ms %d is sleeping\n ",
		(time_sleep - timetamps), (tvars->id + 1));
	while (time <= tvars->sleep)
	{
		gettimeofday (&tv, NULL);
		ntime = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		usleep (100);
		time = (ntime - time_sleep);
	}
	return (0);
}
