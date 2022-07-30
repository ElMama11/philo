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

int	routine_for_optional_arg(t_philo *philo)
{
	while (philo->meal_counter < philo->main->args->nb_meal_required && philo->main->is_dead == 0) //verif la condition
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
	while (philo->main->is_dead == 0) //verif la condition
	{
		if (i_must_eat(philo))
			return (1);
		i_must_sleep(philo);
		i_must_think(philo);
	}
	return (0);
}

void	*philosophers_routine(void *philo_void)
{
	t_philo *philo;

	philo = (t_philo *)philo_void;
	if (philo->meal_counter == -1)
	{
		if (routine_without_optional_arg(philo))
			return (NULL);
	}
	else
		if (routine_without_optional_arg(philo))
			return (NULL);
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
//lancer les philos en meme temps
//tweak les sleep