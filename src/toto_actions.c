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

int	i_must_eat(t_philo *philo)
{
	//if (philo->meal_counter == philo->main->args->nb_meal_required) //les philos doivent-ils continuer a manger apres avoir atteint meal_required?
		//return (1);
	if (take_forks(philo))
		return (1);
	process_lastmeal_time(philo);
	write_something(philo, EAT);
	ms_sleep_with_simulation_ended_check(philo->main->args->time_to_eat, philo);
	if (philo->meal_counter != -1)
		philo->meal_counter++;
	unlock_forks(philo);
	return (0);
}