/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:39:21 by ichouare          #+#    #+#             */
/*   Updated: 2023/02/26 12:31:03 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

int	handlermax(char *str, int i, int sign, int res)
{
	int	j;

	j = 0;
	while (*(str + i) == 48)
		i++;
	while (*(str + i) >= 48 && *(str + i) <= 57)
	{
		i++;
		j++;
	}
	if (j >= 19)
	{
		if (sign < 0)
			return (0);
		return (-1);
	}
	i -= j;
	while ((*(str + i) >= '0' && *(str + i) <= '9')
		&& (*(str + i) != '\0' && *(str + i) != 32 && *(str + i) != '	'))
	{
		res *= 10;
		res += *(str + i) - '0';
		i++;
	}
	return (res * sign);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	int		res;
	char	*ptr;

	i = 0;
	sign = 1;
	res = 0;
	ptr = (char *)nptr;
	while (*(ptr + i) == 32 || (*(ptr + i) >= 9 && *(ptr + i) <= 16))
		i++;
	if (*(ptr + i) == '-')
	{
		sign = -1;
		i++;
	}
	else if (*(ptr + i) == '+')
		i++;
	return (handlermax(ptr, i, sign, res));
}
