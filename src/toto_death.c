#include "philo2.h"

void	check_lock_isdead_variable(t_philo *philo)
{
	pthread_mutex_lock(philo->main->is_dead_mutex);
	philo->main->is_dead = 1;
	pthread_mutex_unlock(philo->main->is_dead_mutex);
}

int	is_philo_dead(t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < philo->main->args->nb_philo)
		{
			pthread_mutex_lock(philo->main->last_meal_mutex);
			if ((get_timestamp(philo->main) - philo->last_meal_time) > philo->main->args->time_to_die)
			{
				pthread_mutex_unlock(philo->main->last_meal_mutex);
				check_lock_isdead_variable(philo);
				return (1);
			}
			pthread_mutex_unlock(philo->main->last_meal_mutex);
			i++;
		}
	}
	return (0);
}

void	join_all_threads(t_main *main)
{
	int i = 0;
	while (i <= main->args->nb_philo)
	{
		pthread_join(main->threads[i], NULL);
		i++;
	}
	return ;
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
			if (is_philo_dead(main->philos[i]))
			{
				write_something(main->philos[i], DEAD);
				return (join_all_threads(main));
			}
			usleep(10);
			i++;
		}
	}
	return (join_all_threads(main));
}