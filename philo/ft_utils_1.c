/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:06:03 by ichouare          #+#    #+#             */
/*   Updated: 2023/02/25 17:25:44 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	printmsg(char *msg, unsigned long time, int id)
{
	printf(msg, time, id);
}

long	get_time(t_philosopher *tvars)
{
	struct timeval	tv;
	long			time;

	gettimeofday (&tv, NULL);
	time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - tvars->begin_time;
	return (time);
}

void	ft_destory(pthread_mutex_t **mutex, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_mutex_destroy(mutex[i]) != 0)
			return ;
		i++;
	}
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
