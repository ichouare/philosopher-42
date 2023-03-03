/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:40:13 by ichouare          #+#    #+#             */
/*   Updated: 2023/02/23 17:01:22 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoBonus.h"

// int ft_strlen(char *str)
// {
//     int i = 0;
//     while(str[i])
//     {
//         i++;
//     }
//     return (i);
// }
int ft_checkparms(int argc, char **argv)
{
    int i = 1;
    int j = 0;
    if(argc < 5 || argc > 6)
        return (0);
    while(i < argc)
    {
        j = 0;
        if(ft_strlen(argv[i]) == 1)
        {
            if(argv[i][j] >= '0' && argv[i][j] <= '9')
               i++;
            else
                return (0);
        }
        else
        {
            j = 0;
            if(argv[i][j] == '+' || (argv[i][j] >= '0' && argv[i][j] <= '9'))
            {
                j++;
                while(argv[i][j])
                {
                    if(argv[i][j] >= '0' && argv[i][j]<= '9')
                        j++;
                    else
                        return (0);
                }
            }
            else
                return (0);
          i++;
        }
    }
    return(1);
}