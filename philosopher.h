/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:32:27 by ichouare          #+#    #+#             */
/*   Updated: 2023/02/05 17:47:08 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>




typedef struct philo
{
    pthread_t i;
    int id;
    int eat;
    int die;
    int sleep;
    int count_eat;
    pthread_mutex_t *mutex;
} t_philosopher;

int ft_atoi(const char *nptr);
#endif