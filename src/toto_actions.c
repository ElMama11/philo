#include "philo2.h"


void	i_must_sleep(t_philo *philo)
{
    write_something(philo, SLEEP);
    ms_sleep(philo->main->args->time_to_sleep);
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

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->main->forks[(philo->id - philo->id % 2) % philo->main->args->nb_philo]);
	pthread_mutex_unlock(philo->main->forks [(philo->id - 1 + (philo->id % 2)) % philo->main->args->nb_philo]);
}

static void	take_forks(t_philo *philo)
{
	// if is_simulation_ended()
		// return 1
	pthread_mutex_lock(philo->main->take_forks);
	// if is_simulation_ended()
		// pthread_mutex_unlock(philo->main->take_forks);
		// return 1
	lock_forks(philo);
	pthread_mutex_unlock(philo->main->take_forks);
	// return 0
}

void	i_must_eat(t_philo *philo)
{
	if (philo->meal_counter == philo->main->args->nb_meal_required)
		return ;
	// if take_forks(philo);
		// return 1

	take_forks(philo);
	philo->last_meal_time = get_timestamp(philo->main) + philo->main->args->time_to_eat;	
	write_something(philo, EAT);
	ms_sleep(philo->main->args->time_to_eat);
	// |                               |
	// V A mettre dans le sleep custom V
	// if is_simulation_ended()
		// unlock_forks(philo);
		// return 1
	// |                               |
	// A A mettre dans le sleep custom A

	philo->meal_counter++;
	unlock_forks(philo);
	return ;
}