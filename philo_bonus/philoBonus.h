/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoBonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:33:14 by ichouare          #+#    #+#             */
/*   Updated: 2023/02/23 15:26:04 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOBONUS_H
#define PHILOBONUS_H

#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include <signal.h>

typedef struct philoProcess
{
    pthread_t thread;
    int pid;
    int id;
    long time_die;
    long time_eat;
    long time_sleep;
    int count_eat;
    long last_eat;
    long begin_time;
    sem_t *semaphore;
    sem_t *sem;
    int number_eat;
} t_philo;

size_t	ft_strlen(const char *str);
int     ft_atoi(const char *nptr);
char	*ft_itoa(int n);
char    *ft_strjoin(char const *s1, char const *s2);
int     ft_checkparms(int argc, char **argv);
#endif

