/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:25:59 by ichouare          #+#    #+#             */
/*   Updated: 2023/03/17 18:09:30 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philoBonus.h"

long	get_time(t_philo *tvars)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - tvars->begin_time;
	return (time);
}

void	printmsg(sem_t **sem, char *msg, unsigned long time, int id)
{
	sem_wait(*sem);
	printf(msg, time, id);
	sem_post(*sem);
}

void	test_die(t_philo *p, long time)
{
	sem_wait (p->sem);
	printf ("%ld ms %d died\n", time, p->id);
	exit (0);
}

void	test(void *data)
{
	t_philo			*p;
	struct timeval	tv;
	long			time;
	long			currentime;

	p = (t_philo *)data;
	time = 0;
	gettimeofday (&tv, NULL);
	currentime = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	time = currentime - p->last_eat;
	if (p->count_eat != -1)
	{
		if (time > p->time_die || p->number_eat >= p->count_eat + 1)
		{
			sem_wait (p->sem);
			if (p->number_eat >= p->count_eat + 1)
				exit (0);
			printf ("%lu ms %d died\n", currentime - p->begin_time, p->id);
			exit (0);
		}
	}
	else
		if (time > p->time_die)
			test_die(p, currentime - p->begin_time);
}

void	ft_eat(t_philo *tvars, sem_t **sem)
{
	struct timeval	tv;
	long			time;
	long			ntime;
	long			time_eat;

	time = 0;
	gettimeofday (&tv, NULL);
	time_eat = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	printmsg(sem, "%lu ms %d is eatingn\n", get_time(tvars), tvars->id);
	tvars->number_eat += 1;
	gettimeofday (&tv, NULL);
	tvars->last_eat = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	while (time <= tvars->time_eat)
	{
		gettimeofday (&tv, NULL);
		ntime = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		usleep (1000);
		time = ntime - time_eat;
	}
}
