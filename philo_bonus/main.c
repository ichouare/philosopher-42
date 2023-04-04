/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:33:44 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/04 13:29:47 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoBonus.h"

void	ft_sleep(t_philo *tvars, sem_t **sem)
{
	struct timeval		tv;
	long				time;
	long				ntime;
	long				time_sleep;

	time = 0;
	gettimeofday (&tv, NULL);
	time_sleep = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	printmsg(sem, "%lu ms %d is sleping\n ", get_time(tvars), tvars->id);
	while (time <= tvars->time_sleep)
	{
		gettimeofday (&tv, NULL);
		ntime = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		usleep (500);
		time = ntime - time_sleep;
	}
}

void	ft_route(t_philo *philos)
{
	while (1)
	{
		sem_wait (philos->semaphore);
		printmsg(&philos->sem, "%ld ms take the %d first fork \n",
			get_time(philos), philos->id);
		sem_wait (philos->semaphore);
		printmsg(&philos->sem, "%ld ms take the %d second fork \n",
			get_time(philos), philos->id);
		ft_eat(philos, &philos->sem);
		sem_post (philos->semaphore);
		sem_post (philos->semaphore);
		ft_sleep(philos, &philos->sem);
		printmsg(&philos->sem, "%ld ms %d is thinking \n",
			get_time(philos), philos->id);
	}
}

t_philo	*ft_init(int argc, char **argv)
{
	int				i;
	struct timeval	tv;
	t_philo			*philos;
	sem_t			*semaphore;
	sem_t			*sem;

	i = 0;
	gettimeofday (&tv, NULL);
	philos = malloc (sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philos)
		exit (0);
	semaphore = sem_open ("fork", O_CREAT, 0644, ft_atoi(argv[1]));
	sem = sem_open ("fprint", O_CREAT, 0644, 1);
	if (sem == SEM_FAILED || semaphore == SEM_FAILED)
		exit (0);
	while (i < ft_atoi(argv[1]))
	{
		philos[i].semaphore = semaphore;
		philos[i].sem = sem;
		philos[i].begin_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		intialise(philos, argc, argv, i);
		i++;
	}
	return (philos);
}

void	ft_child(char **argv, t_philo *philos)
{
	int				i;
	int				j;
	struct timeval	tv;

	i = 0;
	j = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].pid = fork();
		if (philos[i].pid == -1)
			exit (0);
		gettimeofday (&tv, NULL);
		philos[i].last_eat = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		if (philos[i].pid == 0)
		{
			if (pthread_create (&philos[i].thread, NULL,
					(void *)ft_route, &philos[i]) != 0)
				exit (0);
			while (1)
				test(&philos[i]);
		}
		pthread_detach (philos[i].thread);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	int				j;

	j = 0;
	if (ft_checkparms(argc, argv) == 0)
		return (0);
	sem_unlink ("fork");
	sem_unlink ("fprint");
	philos = ft_init(argc, argv);
	ft_child(argv, philos);
	waitpid (-1, NULL, 0);
	while (j < ft_atoi(argv[1]))
	{
		kill (philos[j].pid, SIGKILL);
		j++;
	}
	sem_close (philos->semaphore);
	free (philos);
}
