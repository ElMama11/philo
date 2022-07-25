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

void	wait_until_end(t_main *main)
{
	int i;

	i = 0;

	while (true) {
		int i = 0;
		while i < nb_philo; i++
			if is_philo_dead(philo[i])*
				print_death();
				break ;
			sleep(1)
	}
	
	while (i <= main->args->nb_philo) {
		pthread_join(main->threads[i], NULL);
		i++;
	}

	return ;

}

void	free_memory(t_main *main)
{
	free(main);
}

void	call_death(t_main *main) // void?
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < main->args->nb_philo)
		{
			if ((get_timestamp(main) - main->philos[i]->last_meal_time) > main->args->time_to_die) // call death dans le main?
			{
				//ecrire la mort ds is_dead
				write_something(main->philos[i], DEAD);
			}
			i++;
		}
	}
	// if ((get_timestamp(philo->main) - philo->last_meal_time) > philo->main->args->time_to_die)
	// {
	// 	write_something(philo, DEAD);
	// 	return ;
	// }
}

void	*philosophers_routine(void *philo_void)
{
	t_philo *philo;

	philo = (t_philo *)philo_void;
	printf("id = %d\n", philo->id);
	while (philo->meal_counter < philo->main->args->nb_meal_required)
	{
		// if i_must_eat(philo)
		// 	return NULL;
		i_must_eat(philo)
		i_must_sleep(philo);
		i_must_think(philo);
		// if (call_death(philo))
		// 	return (NULL);
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
// return 1 et 0; clean code dans actions; multiplication de fichier;
//lock qd ecrire et lecture last_meal et pour is_dead
//check simulation_is_ended dans la boucle sleep (50ms) pour eat 