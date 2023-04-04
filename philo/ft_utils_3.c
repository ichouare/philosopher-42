/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:53:24 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/04 12:26:03 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	destory_mutex(t_philosopher **vars, int num)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(vars[i]->print) != 0)
		return (0);
	while (i < num)
	{
		if (pthread_mutex_destroy(vars[i]->time) != 0)
			return (0);
		i++;
	}
	return (1);
}
