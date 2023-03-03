/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:33:44 by ichouare          #+#    #+#             */
/*   Updated: 2023/03/01 13:50:29 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://stackoverflow.com/questions/32205396/share-posix-semaphore-among-multiple-processes


#include "philoBonus.h"

long get_time(t_philo *tvars)
{
    struct timeval tv;    
    long time;
    gettimeofday(&tv, NULL);
    time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - tvars->begin_time;
    return time;
}

void    printMsg(sem_t **sem , char *msg, unsigned long time, int id)
{
    sem_wait(*sem);
    printf(msg, time, id);
    sem_post(*sem);
}

void test(void * data)
{
    t_philo *p =  (t_philo *) data;
    struct  timeval tv;
    long time;
    long currentime;
    time = 0;
        gettimeofday(&tv, NULL);
        currentime = ((tv.tv_sec * 1000 ) + (tv.tv_usec / 1000));
        time = currentime - p->last_eat;
        if(p->count_eat != -1)
        {
            if(time > p->time_die || p->number_eat >= p->count_eat  + 1)
            {
                sem_wait(p->sem);
                if(p->number_eat >= p->count_eat + 1)
                    exit(0);
                printf("%lu ms %d died\n", currentime - p->begin_time, p->id);
                exit(0); 
            } 
        }
        else
        {
            if(time > p->time_die)
            {
                sem_wait(p->sem);
                printf("%lu ms %d died\n", currentime - p->begin_time, p->id);
                exit(0);
             }      
        }
         
}

void ft_eat(t_philo *tvars, sem_t **sem)
{
    struct timeval tv;
    long  time;
    long   ntime;
    long time_eat;
    time = 0;
    gettimeofday(&tv, NULL);
    time_eat = ((tv.tv_sec * 1000)  + (tv.tv_usec / 1000));
    printMsg(sem, "%lu ms %d is eatingn\n ",get_time(tvars),tvars->id);
    tvars->number_eat +=1;
    gettimeofday(&tv, NULL); 
    tvars->last_eat = ((tv.tv_sec * 1000 ) + (tv.tv_usec / 1000));
    while(time <= tvars->time_eat)
    {
        gettimeofday(&tv, NULL);
        ntime =  (tv.tv_sec * 1000)  + (tv.tv_usec / 1000);
        usleep(1000);
        time = ntime - time_eat;
    }
}


void ft_sleep(t_philo *tvars, sem_t **sem)
{
    struct timeval tv;
    long  time;
    long   ntime;
    long time_sleep;

    time  = 0;
    gettimeofday(&tv, NULL);
    time_sleep = ((tv.tv_sec * 1000)  + (tv.tv_usec / 1000));
    printMsg(sem, "%lu ms %d is sleping\n ",get_time(tvars),tvars->id);
    while(time <= tvars->time_sleep)
    {
        gettimeofday(&tv, NULL);
        ntime =  (tv.tv_sec * 1000)  + (tv.tv_usec / 1000);
        usleep(1000);
        time = ntime - time_sleep;
    }
}
void ft_route(t_philo *philos)
{
    while(1)
    {
        sem_wait(philos->semaphore);
        printMsg(&philos->sem, "%ld ms take the %d first fork \n", get_time(philos), philos->id); 
        sem_wait(philos->semaphore);
        printMsg(&philos->sem, "%ld ms take the %d second fork \n", get_time(philos), philos->id); 
        ft_eat(philos, &philos->sem);
        sem_post(philos->semaphore);
        sem_post(philos->semaphore);
        ft_sleep(philos, &philos->sem);
        printMsg(&philos->sem, "%ld ms %d is thinking \n", get_time(philos), philos->id); 
    }   
}

t_philo *ft_init(int argc, char **argv)
{
    int i = 0;
    struct timeval tv;
    int number_of_philo = ft_atoi(argv[1]);
    gettimeofday(&tv, NULL);
    t_philo *philos;
    sem_t *semaphore;
    sem_t *sem;
    
    philos =  malloc(sizeof(t_philo ) * number_of_philo);
    semaphore = sem_open("fork", O_CREAT, 0644, ft_atoi(argv[1]));
    sem = sem_open("fprint", O_CREAT, 0644, 1);
    
    while(i < number_of_philo)
    {
        philos[i].id =  i + 1;
        philos[i].time_die =  ft_atoi(argv[2]);
        philos[i].time_eat =  ft_atoi(argv[3]);
        philos[i].time_sleep =  ft_atoi(argv[4]);
        philos[i].semaphore = semaphore;
        philos[i].sem = sem;
        philos[i].begin_time =  (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
        philos[i].number_eat = 0;
        if(argc == 6)
            philos[i].count_eat =  ft_atoi(argv[5]);
        else
            philos[i].count_eat = -1;
        i++;
    }
    return (philos);
    
}

int main(int argc, char **argv)
{
    t_philo *philos;
    int i;
    int j;
    struct timeval tv;
    
    if( ft_checkparms(argc, argv) == 0)
            return (0);
    sem_unlink("fork");
    sem_unlink("fprint");
    philos = ft_init(argc, argv);
    i = 0;
    j = 0;
    while(i < ft_atoi(argv[1]))
    { 
        philos[i].pid = fork();
        gettimeofday(&tv, NULL);
        philos[i].last_eat = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
        if(philos[i].pid == 0)
        { 
            if(i % 2)
                usleep(1000);
            pthread_create(&philos[i].thread, NULL, (void *)ft_route, &philos[i]);
            while(1)
                test(&philos[i]);
        }
    pthread_detach(philos[i].thread);
        i++;
    }
    waitpid(-1, NULL, 0);
    while(j < ft_atoi(argv[1]))
    {
        kill(philos[j].pid, SIGKILL);
        j++;
    }
    sem_close(philos->semaphore);
    free(philos);
    
    
    
      
   
    
    
    
}