#include "philo2.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->main->take_forks);
	pthread_mutex_lock(philo->main->forks[(philo->id - philo->id % 2) % philo->main->args->nb_philo]);
	write_something(philo, FORK);
    pthread_mutex_lock(philo->main->forks [(philo->id - 1 + (philo->id % 2)) % philo->main->args->nb_philo]);
	write_something(philo, FORK);
	pthread_mutex_unlock(philo->main->take_forks);
}

int	i_must_sleep(t_philo *philo)
{
    write_something(philo, SLEEP);
    ms_sleep(philo->main->args->time_to_sleep);
	return (1);
}

int	i_must_think(t_philo *philo)
{
	write_something(philo, THINK);
	return (1);
}


int	i_must_eat(t_philo *philo)
{
	if (philo->meal_counter == philo->main->args->nb_meal_required)
		return (0);
	take_forks(philo);
	philo->last_meal_time = get_timestamp(philo->main) + philo->main->args->time_to_eat;	
	write_something(philo, EAT);
	philo->meal_counter++;
	ms_sleep(philo->main->args->time_to_eat);
	pthread_mutex_unlock(philo->main->forks[(philo->id - philo->id % 2) % philo->main->args->nb_philo]);
	pthread_mutex_unlock(philo->main->forks [(philo->id - 1 + (philo->id % 2)) % philo->main->args->nb_philo]);
	return (1);
}