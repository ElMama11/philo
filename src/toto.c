#include "philo2.h"
//[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]
void	write_something(t_philo *philo, char *message)
{
	if (message == FORK)
		printf(FORK, philo->id, get_timestamp(philo->main));
	else if (message == EAT)
		printf(EAT, philo->id, get_timestamp(philo->main));
	else if (message == SLEEP)
		printf(SLEEP, philo->id, get_timestamp(philo->main));
	else if (message == THINK)
		printf(THINK, philo->id, get_timestamp(philo->main));
	else if (message == DEAD)
		printf(DEAD, philo->id, get_timestamp(philo->main));
}

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


void	free_memory(t_main *main)
{
	free(main);
}

void	*philosophers_routine(void *philo_void)
{
	t_philo *philo;

	philo = (t_philo *)philo_void;
	//printf("id = %d\n", philo->id);
	while (philo->meal_counter < philo->main->args->nb_meal_required)
	{
		if (i_must_eat(philo))
			return (NULL);
		i_must_sleep(philo);
		i_must_think(philo);
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
//lock qd ecrire et lecture last_meal
//check ms sleep dans i must sleep