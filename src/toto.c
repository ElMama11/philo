#include "philo2.h"

void write_something(t_philo *philo, char *message)
{
	if (message == FORK)
		printf(FORK, philo->id, get_timestamp(philo->main));
	else if (message == EAT)
		printf(EAT, philo->id, get_timestamp(philo->main));
	else if (message == SLEEP)
		printf( SLEEP, philo->id, get_timestamp(philo->main));
	else if (message == THINK)
		printf(THINK, philo->id, get_timestamp(philo->main));
	else if (message == DEAD)
		printf(DEAD, philo->id, get_timestamp(philo->main));
}

void	wait_until_end(t_main *main)
{
	int i;

	i = 0;
	while (i <= main->args->nb_philo) {
		pthread_join(main->threads[i], NULL);
		i++;
	}
}

void	free_memory(t_main *main)
{
	free(main);
}

void i_must_sleep(t_philo *philo)
{
    write_something(philo, SLEEP);
    ms_sleep(philo->main->args->time_to_sleep);
}

int	i_must_eat(t_philo *philo)
{
	if (philo->meal_counter == philo->main->args->nb_meal_required)
		return (0);
	// LOCK GLOBAL
	pthread_mutex_lock(philo->main->forks[(philo->id - philo->id % 2) % philo->main->args->nb_philo]);
	write_something(philo, FORK);
    pthread_mutex_lock(philo->main->forks [(philo->id - 1 + (philo->id % 2)) % philo->main->args->nb_philo]);
	write_something(philo, FORK);
	// UNLOCK()
	philo->last_meal_time = get_timestamp(philo->main) + philo->main->args->time_to_eat;	
	write_something(philo, EAT);
	philo->meal_counter++;
	ms_sleep(philo->main->args->time_to_eat);
	pthread_mutex_unlock(philo->main->forks[(philo->id - philo->id % 2) % philo->main->args->nb_philo]);
	pthread_mutex_unlock(philo->main->forks [(philo->id - 1 + (philo->id % 2)) % philo->main->args->nb_philo]);
	return (1);
}

void	*philosophers_routine(void *philo_void)
{
	t_philo *philo;

	philo = (t_philo *)philo_void;
	printf("id = %d\n", philo->id);
	while (1)
	{
		if (i_must_eat(philo))
			write_something(philo, EAT);
		else if (i_must_sleep(philo))
		 	write_something(philo, SLEEP);
		else if (i_must_think())
			write_something(philo, THINK);
		// if (call_death())
		// 	break;	
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_main *main;

	main = (t_main*)malloc(sizeof(t_main));
	memset(main, 0, sizeof(t_main));
	if (parsing(main, ac, av))
		return (1);
	init(main);
	wait_until_end(main);
	free_memory(main);
	return (0);
}