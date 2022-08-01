#include "philo2.h"

void lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->main->forks[(philo->id - philo->id % 2) % philo->main->args->nb_philo]);
	write_something(philo, 1);
	pthread_mutex_lock(philo->main->forks[(philo->id - 1 + (philo->id % 2)) % philo->main->args->nb_philo]); // deadlock pour 1 philo
	write_something(philo, 1);
}

void unlock_forks(t_philo *philo)
{
	printf("Thread %d: Unlock forks %d\n", philo->id, (philo->id - philo->id % 2) % philo->main->args->nb_philo);
	pthread_mutex_unlock(philo->main->forks[(philo->id - philo->id % 2) % philo->main->args->nb_philo]);
	printf("Thread %d: Unlock forks %d\n", philo->id, (philo->id - 1 + (philo->id % 2)) % philo->main->args->nb_philo);
	pthread_mutex_unlock(philo->main->forks[(philo->id - 1 + (philo->id % 2)) % philo->main->args->nb_philo]);
}

int take_forks(t_philo *philo)
{
	if (philo->main->args->nb_philo == 1)
		return (1);
	if (is_simulation_ended(philo))
		return (1);
	// pthread_mutex_lock(philo->main->take_forks);
	if (is_simulation_ended(philo))
	{
		// pthread_mutex_unlock(philo->main->take_forks);
		return (1);
	}
	lock_forks(philo);
	// pthread_mutex_unlock(philo->main->take_forks);
	return (0);
}

int is_simulation_ended(t_philo *philo)
{
	pthread_mutex_lock(philo->main->is_dead_mutex);
	if (philo->main->is_dead == 1)
	{
		pthread_mutex_unlock(philo->main->is_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->main->is_dead_mutex);
	return (0);
}

void process_lastmeal_time(t_philo *philo)
{
	pthread_mutex_lock(philo->main->last_meal_mutex);
	philo->last_meal_time = get_timestamp(philo->main) + philo->main->args->time_to_eat;
	pthread_mutex_unlock(philo->main->last_meal_mutex);
}
