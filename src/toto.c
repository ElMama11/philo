#include "philo2.h"
//[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]
void	write_something(t_philo *philo, int message)
{
	if (! is_simulation_ended(philo) && ! is_eatings_completed(philo->main)) {
		pthread_mutex_lock(philo->main->message);
		if (message == 1)
			printf(FORK, philo->id, get_timestamp(philo->main), philo->meal_counter);
		else if (message == 2)
			printf(EAT, philo->id, get_timestamp(philo->main), philo->meal_counter);
		else if (message == 3)
			printf(SLEEP, philo->id, get_timestamp(philo->main), philo->meal_counter);
		else if (message == 4)
			printf(THINK, philo->id, get_timestamp(philo->main), philo->meal_counter);
		pthread_mutex_unlock(philo->main->message);
	}
	if (message == 5) {
		pthread_mutex_lock(philo->main->message);
		printf(DEAD, philo->id, get_timestamp(philo->main), philo->meal_counter);
		pthread_mutex_unlock(philo->main->message);
	}
}

int	routine_for_optional_arg(t_philo *philo)
{
	while (philo->meal_counter != philo->main->args->nb_meal_required && ! is_simulation_ended(philo) && ! is_eatings_completed(philo->main)) //verif la condition
	{
		if (i_must_eat(philo))
			return (1);
		i_must_sleep(philo);
		i_must_think(philo);
	}
	return (0);
}

int	routine_without_optional_arg(t_philo *philo)
{
	while (! is_simulation_ended(philo) && ! is_eatings_completed(philo->main)) //verif la condition
	{
		if (i_must_eat(philo))
			return (1);
		i_must_sleep(philo);
		i_must_think(philo);
	}
	return (0);
}

void wait_for_start_signal(t_main *main)
{
	//pthread_mutex_lock(main->signal_mutex);
	while (main->signal != 1)
	{
		//pthread_mutex_unlock(main->signal_mutex);
		usleep(1);
	}
	//pthread_mutex_unlock(main->signal_mutex);
}

void	*philosophers_routine(void *philo_void)
{
	t_philo *philo;

	philo = (t_philo *)philo_void;
	wait_for_start_signal(philo->main);
	if (philo->meal_counter == -1)
	{
		if (routine_without_optional_arg(philo))
			return (NULL);
	}
	else
		if (routine_for_optional_arg(philo))
			return (NULL);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_main main;

	//main = (t_main*)malloc(sizeof(t_main));
	memset(&main, 0, sizeof(t_main));
	if (parsing(&main, ac, av))
		return (1);
	init(&main);
	wait_until_end(&main);
	//free_memory(&main);
	return (0);
}
//lancer les philos en meme temps
//tweak les sleep
//mutex le signal wsl2