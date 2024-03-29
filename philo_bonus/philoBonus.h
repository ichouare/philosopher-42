/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoBonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:33:14 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/04 11:08:36 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILOBONUS_H
# define PHILOBONUS_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct philoProcess
{
	pthread_t	thread;
	int			pid;
	int			id;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	int			count_eat;
	long		last_eat;
	long		begin_time;
	sem_t		*semaphore;
	sem_t		*sem;
	sem_t		*eat;
	int			number_eat;
}	t_philo;

long		get_time(t_philo *tvars);
void		printmsg(sem_t **sem, char *msg, unsigned long time, int id);
void		test(void *data);
void		intialise(t_philo *philos, int argc, char **argv, int i);
void		ft_eat(t_philo *tvars, sem_t **sem);
size_t		ft_strlen(const char *str);
int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_checkparms(int argc, char **argv);
void		ft_decal(int id);
void		ft_test_die(long time, long curentime, t_philo *p);
void		test_die(t_philo *p, long time);
#endif
