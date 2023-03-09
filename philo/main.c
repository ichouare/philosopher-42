/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:56:14 by ichouare          #+#    #+#             */
/*   Updated: 2023/03/09 21:55:16 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_eat(t_philosopher *tvars, long timetamps)
{
	struct timeval	tv;
	struct timeval	timeeat;
	long			time;
	long			ntime;
	long			time_eat;

	gettimeofday (&timeeat, NULL);
	time_eat = (timeeat.tv_sec * 1000) + (timeeat.tv_usec / 1000);
	time = 0;
	tvars->number_eat += 1;
	printmsg("%lu ms %d is eatingn\n ", (time_eat - timetamps),
		(tvars->id + 1), tvars->print);
	while (time <= tvars->eat)
	{
		gettimeofday (&tv, NULL);
		ntime = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		usleep (100);
		time = (ntime - time_eat);
	}
	return (0);
}

void	dead(t_philosopher *vars, char **argv, int argc)
{
	int	i;
	int	j;

	while (1)
	{
		i = 0;
		j = 0;
		while (i < ft_atoi(argv[1]))
		{
			if (argc == 6)
				if (vars[i].number_eat >= vars[i].count_eat)
					j++;
			if (ft_die(&vars[i]) == 1)
				return ;
			i++;
			if (j == (ft_atoi(argv[1])))
				return ;
		}
	}
}

pthread_mutex_t	*create_mutex(int num)
{
	pthread_mutex_t	*mutex;
	int				i;

	i = 0;
	mutex = malloc (sizeof (pthread_mutex_t) * num);
	if (mutex == NULL)
		return (0);
	while (i < num)
	{
		if (pthread_mutex_init(&mutex[i], NULL) != 0)
			return (0);
		i++;
	}
	return (mutex);
}

t_philosopher	*t_allocate_thread(int n)
{
	t_philosopher	*vars;

	vars = malloc (sizeof(t_philosopher) * n);
	if (vars == NULL)
		return (0);
	return (vars);
}

t_philosopher	*ft_init(int ag, char **av, int n, pthread_mutex_t **mutex)
{
	t_philosopher	*vars;
	struct timeval	tms;
	int				i;
	pthread_mutex_t	*print_mutex;

	i = 0;
	vars = t_allocate_thread(n);
	gettimeofday (&tms, NULL);
	print_mutex = create_mutex(1);
	while (i < n)
	{
		vars[i].begin_time = (tms.tv_sec * 1000) + (tms.tv_usec / 1000);
		vars[i].last_eat = vars[i].begin_time;
		vars[i].id = i;
		vars[i].nthreads = ft_atoi(av[1]);
		vars[i].die = ft_atoi(av[2]);
		vars[i].eat = ft_atoi(av[3]);
		vars[i].sleep = ft_atoi(av[4]);
		vars[i].number_eat = 0;
		vars[i].print = print_mutex;
		if (ag == 6)
			vars[i].count_eat = ft_atoi(av[5]);
		vars[i++].mutex = *mutex;
	}
	return (vars);
}

int	main(int argc, char **argv)
{
	t_philosopher	*vars;
	pthread_mutex_t	*mutex;
	int				i;

	if (ft_checkparms(argc, argv) == 0)
		return (0);
	mutex = create_mutex(ft_atoi(argv[1]));
	vars = ft_init(argc, argv, ft_atoi(argv[1]), &mutex);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_create(&vars[i].i, NULL, test, &vars[i]) != 0)
			return (0);
		i++;
	}
	ft_detach(&vars, ft_atoi(argv[1]));
	dead(vars, argv, argc);
	ft_destory(&mutex, ft_atoi(argv[1]));
}
