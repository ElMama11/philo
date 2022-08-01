#include "philo2.h"

static void init_mutex(t_main *main)
{
	main->take_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(main->take_forks, NULL);
	main->is_dead_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(main->is_dead_mutex, NULL);
	main->last_meal_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(main->last_meal_mutex, NULL);
	main->message = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(main->message, NULL);
	main->signal_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(main->signal_mutex, NULL);
	main->meal_counter_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(main->meal_counter_mutex, NULL);
}

static int create_forks(t_main *main)
{
	int i;

	i = 0;
	main->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * main->args->nb_philo);
	if (main->forks == NULL)
		return (1);
	while (i < main->args->nb_philo)
	{
		main->forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * main->args->nb_philo);
		if (pthread_mutex_init(main->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int create_philo_structs(t_main *main)
{
	int i;

	i = 0;

	main->philos = (t_philo **)malloc(sizeof(t_philo *) * main->args->nb_philo);
	while (i < main->args->nb_philo)
	{
		main->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		memset(main->philos[i], 0, sizeof(t_philo));
		main->philos[i]->id = i + 1;
		main->philos[i]->main = main;
		if (main->args->nb_meal_required == -1)
			main->philos[i]->meal_counter = -1;

		i++;
	}
	return (0);
}

static int create_philo_threads(t_main *main)
{
	int i;
	int ret;

	i = 0;
	pthread_mutex_lock(main->signal_mutex);
	while (i < main->args->nb_philo)
	{
		ret = pthread_create(&(main->threads[i]), NULL, (void *)philosophers_routine, (void *)(main->philos[i]));
		if (ret != 0)
		{
			printf("thread error\n");
			return (1);
		}
		i++;
	}
	main->start_time = ft_get_time();
	pthread_mutex_unlock(main->signal_mutex);
	return (0);
}

// static int	create_death_thread(t_main *main)
// {
// 	int	ret;
// 	main->death = (pthread_t *)malloc(sizeof(pthread_t));
// 	ret = pthread_create(main->death, NULL, (void *)call_death, (void *)(main));
// 		if (ret != 0)
// 		{
// 			printf("thread error\n");
// 			return (1);
// 		}
// 	return (0);
// }

void init(t_main *main)
{
	create_forks(main);
	create_philo_structs(main);
	init_mutex(main);
	create_philo_threads(main);
	// create_death_thread(main);
}
