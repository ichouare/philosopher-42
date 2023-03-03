/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:29:53 by ichouare          #+#    #+#             */
/*   Updated: 2023/02/20 13:34:13 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philoBonus.h"

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}