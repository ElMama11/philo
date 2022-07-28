#include "philo2.h"


void	i_must_sleep(t_philo *philo)
{
    write_something(philo, SLEEP);
    ms_sleep_with_simulation_ended_check(philo->main->args->time_to_sleep, philo);
}

void	i_must_think(t_philo *philo)
{
	write_something(philo, THINK);
}

static void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->main->forks[(philo->id - philo->id % 2) % philo->main->args->nb_philo]);
	write_something(philo, FORK);
	pthread_mutex_lock(philo->main->forks [(philo->id - 1 + (philo->id % 2)) % philo->main->args->nb_philo]);
	write_something(philo, FORK);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->main->forks[(philo->id - philo->id % 2) % philo->main->args->nb_philo]);
	pthread_mutex_unlock(philo->main->forks [(philo->id - 1 + (philo->id % 2)) % philo->main->args->nb_philo]);
}

int	is_simulation_ended(t_philo *philo)
{
	if (philo->main->is_dead == 1)
		return (1);
	else
		return (0);
}

static int	take_forks(t_philo *philo)
{
	if (is_simulation_ended(philo))
		return (1);
	pthread_mutex_lock(philo->main->take_forks); //is_dead = 1??
	if (is_simulation_ended(philo))
	{
		pthread_mutex_unlock(philo->main->take_forks);
		return (1);
	}
	lock_forks(philo);
	pthread_mutex_unlock(philo->main->take_forks);
	return (0);
}

void	process_lastmeal_time(t_philo *philo)
{
	pthread_mutex_lock(philo->main->last_meal_mutex);
	philo->last_meal_time = get_timestamp(philo->main) + philo->main->args->time_to_eat;
	pthread_mutex_unlock(philo->main->last_meal_mutex);
}

int	i_must_eat(t_philo *philo)
{
	if (philo->meal_counter == philo->main->args->nb_meal_required)
		return (1);
	if (take_forks(philo))
		return (1);
	process_lastmeal_time(philo);
	write_something(philo, EAT);
	ms_sleep_with_simulation_ended_check(philo->main->args->time_to_eat, philo);
	philo->meal_counter++;
	unlock_forks(philo);
	return (0);
}