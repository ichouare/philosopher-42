/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:40:13 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/08 15:08:19 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoBonus.h"

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

	j = 0;
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

void	intialise(t_philo *philos, int argc, char **argv, int i)
{
	sem_unlink (ft_itoa(i));
	philos[i].id = i + 1;
	philos[i].time_die = ft_atoi(argv[2]);
	philos[i].time_eat = ft_atoi(argv[3]);
	philos[i].time_sleep = ft_atoi(argv[4]);
	philos[i].number_eat = 0;
	philos[i].count_eat = -1;
	philos[i].eat = sem_open (ft_itoa(i), O_CREAT, 0644, 1);
	if (philos[i].eat == SEM_FAILED)
		exit (0);
	if (argc == 6)
		philos[i].count_eat = ft_atoi(argv[5]);
	return ;
}

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
