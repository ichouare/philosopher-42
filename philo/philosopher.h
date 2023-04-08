/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:32:27 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/08 12:24:01 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct philo
{
	pthread_t		i;
	int				nthreads;
	int				id;
	int				eat;
	int				die;
	int				sleep;
	int				count_eat;
	long			last_eat;
	long			begin_time;
	int				number_eat;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
	pthread_mutex_t	*time;
}	t_philosopher;

long			get_time(t_philosopher *tvars);
void			ft_decal(int id);
t_philosopher	*t_allocate_thread(int n);
void			printmsg(char *msg, unsigned long time, int id,
					pthread_mutex_t *print);
int				ft_destory(pthread_mutex_t **mutex, int num);
void			ft_detach(t_philosopher **vars, int num);
int				ft_sleep(t_philosopher *tvars, long timetamps);
int				ft_eat(t_philosopher *tvars, long timetamps);
int				ft_strlen(char *str);
int				ft_checkparms(int argc, char **argv);
int				ft_atoi(const char *nptr);
void			*test(void *vars);
int				ft_die(t_philosopher *tvars);
void			ft_usleep(int num);
void			ft_clock(t_philosopher	*p);
void			init_thread(t_philosopher *vars, char **av, int ag);
int				destory_mutex(t_philosopher **vars, int num);

#endif