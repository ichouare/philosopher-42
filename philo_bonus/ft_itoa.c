/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:27:10 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/04 12:26:58 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philoBonus.h"

static int	len_int(int n)
{
	int	i;
	int	number;

	i = 0;
	number = n;
	if (n == 0)
		return (1);
	while (number != 0)
	{
		number /= 10;
		i++;
	}
	if (n < 0)
		i++;
	return (i);
}

static char	*handlertable(char *arr, int n, int i)
{
	int				j;
	int				last;
	unsigned int	number;

	j = 0;
	last = 0;
	number = n;
	if (n < 0)
	{
		arr[0] = '-';
		number *= -1;
		last++;
	}
	j = i - 1;
	while (j >= last)
	{
		arr[j] = (number % 10) + '0';
		number /= 10;
		j--;
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*arr;
	unsigned int	number;

	number = n ;
	i = len_int(number);
	arr = (char *)malloc(sizeof(char) * (i + 1));
	if (!arr)
		return (NULL);
	handlertable(arr, n, i);
	return (arr);
}

void	ft_test_die(long time, long curentime, t_philo *p)
{
	if (time > p->time_die)
		test_die(p, curentime - p->begin_time);
	return ;
}
