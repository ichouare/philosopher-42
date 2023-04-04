/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:25:59 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/03 18:16:39 by ichouare         ###   ########.fr       */
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
	sem_wait(p->eat);
	time = currentime - p->last_eat;
	sem_post(p->eat);
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
		ft_test_die(time, currentime, p);
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
	printmsg(sem, "%ld ms %d is eating\n", get_time(tvars), tvars->id);
	tvars->number_eat += 1;
	gettimeofday (&tv, NULL);
	sem_wait(tvars->eat);
	tvars->last_eat = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	sem_post(tvars->eat);
	while (time <= tvars->time_eat)
	{
		gettimeofday (&tv, NULL);
		ntime = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		usleep (500);
		time = ntime - time_eat;
	}
}
