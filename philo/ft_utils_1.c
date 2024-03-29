/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:06:03 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/04 11:58:16 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	printmsg(char *msg, unsigned long time, int id, pthread_mutex_t *print)
{
	pthread_mutex_lock(print);
	printf(msg, time, id);
	pthread_mutex_unlock(print);
}

long	get_time(t_philosopher *tvars)
{
	struct timeval	tv;
	long			time;

	gettimeofday (&tv, NULL);
	time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - tvars->begin_time;
	return (time);
}

int	ft_destory(pthread_mutex_t **mutex, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_mutex_destroy(mutex[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_detach(t_philosopher **vars, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_detach(vars[i]->i) != 0)
			return ;
		i++;
	}
}
