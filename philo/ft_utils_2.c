/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:55:52 by ichouare          #+#    #+#             */
/*   Updated: 2023/03/28 15:45:55 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_decal(int id)
{
	int	j;

	j = 0;
	if (id % 2)
	{
		while (j < 500)
		{
			usleep (1);
			j++;
		}
	}
}

t_philosopher	*t_allocate_thread(int n)
{
	t_philosopher	*vars;

	vars = malloc (sizeof(t_philosopher) * n);
	if (vars == NULL)
		return (0);
	return (vars);
}

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
