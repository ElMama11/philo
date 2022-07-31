#include "philo2.h"

void	check_lock_isdead_variable(t_philo *philo)
{
	pthread_mutex_lock(philo->main->is_dead_mutex);
	philo->main->is_dead = 1;
	pthread_mutex_unlock(philo->main->is_dead_mutex);
}

int is_philo_satisfied(t_philo *philo)
{
	if (philo->main->args->nb_meal_required == -1)
		return (0);
	if (philo->meal_counter == philo->main->args->nb_meal_required) {
		return (1);
	}
	return (0);
}

int	is_philo_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->main->args->nb_philo)
	{
		pthread_mutex_lock(philo->main->last_meal_mutex); //un lock par philo
		if (! is_philo_satisfied(philo) && (get_timestamp(philo->main) - philo->last_meal_time) > philo->main->args->time_to_die)
		{
			pthread_mutex_unlock(philo->main->last_meal_mutex);
			check_lock_isdead_variable(philo);
			return (1);
		}
		pthread_mutex_unlock(philo->main->last_meal_mutex);
		i++;
	}
	return (0);
}

void	join_all_threads(t_main *main)
{
	int i = 0;
	while (i < main->args->nb_philo)
	{
		pthread_join(main->threads[i], NULL);
		i++;
	}
	return ;
}

int	is_eatings_completed(t_main *main) {
	int i = 0;
	int sum = main->args->nb_meal_required * main->args->nb_philo;
	int counter = 0;

	if (main->args->nb_meal_required == -1)
		return (0);
	while (i < main->args->nb_philo) {
		counter += main->philos[i]->meal_counter;
		i++;
	}
	if (counter == sum)
		return (1);
	return (0);
}

void	wait_until_end(t_main *main)
{
	int i;

	i = 0;

	while (1)
	{
		int i = 0;
		while (i < main->args->nb_philo)
		{
			if (is_eatings_completed(main))
				return (join_all_threads(main));
			else if (is_philo_dead(main->philos[i]))
			{
				write_something(main->philos[i], 5);
				return (join_all_threads(main));
			}
			ms_sleep(1);
			i++;
		}
	}
	return (join_all_threads(main));
}