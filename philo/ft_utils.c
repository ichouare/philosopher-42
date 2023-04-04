/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:54:04 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/04 12:11:21 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	more_check(char **argv, int *i)
{
	int	j;

	j = 0;
	if (argv[*i][j] == '+' || (argv[*i][j] >= '0' && argv[*i][j] <= '9'))
	{
		j++;
		while (argv[*i][j])
		{
			if (argv[*i][j] >= '0' && argv[*i][j] <= '9')
				j++;
			else
				return (0);
		}
	}
	else
		return (0);
	*i = *i + 1;
	return (1);
}

int	ft_checkparms(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
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
			if (more_check(argv, &i) == 0)
				return (0);
	}
	return (1);
}

void	*test(void *vars)
{
	t_philosopher	*p;
	struct timeval	timestamp;
	long			time;

	p = (t_philosopher *)vars;
	time = p->begin_time;
	ft_decal(p->id);
	while (1)
	{
		pthread_mutex_lock (&p->mutex[p->id]);
		printmsg("%ld ms take the %d first fork \n", get_time(p),
			(p->id + 1), p->print);
		pthread_mutex_lock (&p->mutex[(p->id + 1) % p->nthreads]);
		printmsg("%ld ms take the %d second fork \n", get_time(p),
			(p->id + 1), p->print);
		gettimeofday (&timestamp, NULL);
		ft_clock(p);
		ft_eat(vars, time);
		pthread_mutex_unlock (&p->mutex[p->id]);
		pthread_mutex_unlock (&p->mutex[(p->id + 1) % p->nthreads]);
		ft_sleep(vars, time);
		printmsg("%ld ms %d  is thinking\n",
			get_time(p), (p->id + 1), p->print);
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
	pthread_mutex_lock(tvars->time);
	time = currenttime - tvars->last_eat;
	pthread_mutex_unlock(tvars->time);
	if (time > tvars->die)
	{
		pthread_mutex_lock(tvars->print);
		printf("%lu ms %d died",
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
	printmsg("%ld ms %d is sleeping\n ",
		(time_sleep - timetamps), (tvars->id + 1), tvars->print);
	while (time <= tvars->sleep)
	{
		gettimeofday (&tv, NULL);
		ntime = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		usleep (500);
		time = (ntime - time_sleep);
	}
	return (0);
}
