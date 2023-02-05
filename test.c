#include "philosopher.h"




void *test(void *vars){
    t_philosopher  *p = (t_philosopher *)vars;
    printf("---- the thread %d thinking --- \n ", p->id);
    pthread_mutex_lock(&p->mutex[p->id]);
    printf("the thread  %d take first fork \n",p->id);
    pthread_mutex_lock(&p->mutex[p->id + 1]);
    printf("the thread  %d  take second fork\n",p->id + 1);
    printf("---- the thread %d eating --- \n ", p->id);
    pthread_mutex_unlock(&p->mutex[p->id]);
    pthread_mutex_unlock(&p->mutex[p->id + 1]);
    return NULL;
}


int main(int argc, char **argv)
{
   
    t_philosopher *vars;
    pthread_mutex_t     *mutex;
    int number_of_philosopher;
    int i = 0;
    if(argc != 6)
        return (0);
    number_of_philosopher = ft_atoi(argv[1]);
    mutex = malloc(sizeof(pthread_mutex_t) * 5);
    if(mutex == NULL)
        return (0);
    while(i < number_of_philosopher)
    {
        if(pthread_mutex_init(&mutex[i], NULL) != 0)
            return (0);
        i++;
    }

    vars = malloc(sizeof(t_philosopher) * 5);
    if(vars == NULL)
        return (0);
    i = 0;
    while(i < number_of_philosopher)
    {
        vars[i].id = i;
        vars[i].eat = ft_atoi(argv[2]);
        vars[i].die = ft_atoi(argv[2]);
        vars[i].sleep = ft_atoi(argv[2]);
        vars[i].count_eat = ft_atoi(argv[2]);
        vars[i].mutex = mutex;
        i++;
    }
    i = 0;
    while( i < number_of_philosopher)
    {
        if(pthread_create(&vars[i].i, NULL, test, &vars[i]) != 0)
            return(0);
        i++;
    }
    i = 0;
    while(i < number_of_philosopher)
    {
        if(pthread_join(vars[i].i, NULL) != 0)
            return(0);
        i++;
    }
    i = 0;
    while(i < number_of_philosopher)
    {
        if(pthread_mutex_destroy(&vars->mutex[i])!= 0)
            return(0);
        i++;
    }
    
}  