/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:51:17 by mverger           #+#    #+#             */
/*   Updated: 2022/07/06 19:55:05 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"
//[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]

int message (t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->global->death);
	if (philo->global->is_dead == 1)
	{
		pthread_mutex_unlock(philo->global->death);
		return (1);
	}
	pthread_mutex_unlock(philo->global->death);
	pthread_mutex_lock(philo->global->message);
	if (message != DEAD)
		printf(message, get_timestamp(philo->global), philo->id);
	else if (message == DEAD)
	{
		printf(DEAD, get_timestamp(philo->global), philo->id);
		pthread_mutex_unlock(philo->global->message);
		return (1);	
	}
	pthread_mutex_unlock(philo->global->message);
	return (0);
}

int ft_sleep(t_philo *philo)
{
    if (message(philo, SLEEP))
        return (1);
    ms_sleep(philo->global->time_to_sleep);
    return (0);
}

int	eat(t_philo *philo)
{
	int	time;
	
	time = 0;
	if (philo->meal_counter == philo->global->nb_meal_required)
		return (1);
	pthread_mutex_lock(philo->global->forks[(philo->id - philo->id % 2) % philo->global->nb_philo]);
    if (message(philo, FORK))
        return (1);
    pthread_mutex_lock(philo->global->forks [(philo->id - 1 + (philo->id % 2)) % philo->global->nb_philo]);
    if (message(philo, FORK))
        return (1);
	pthread_mutex_lock(philo->last_meal);
	philo->last_meal_time = get_timestamp(philo->global) + philo->global->time_to_eat;
	pthread_mutex_unlock(philo->last_meal);
	if (message(philo, EAT))
        return (1);
	philo->meal_counter++;
	ms_sleep(philo->global->time_to_eat);
	pthread_mutex_lock(philo->last_meal);
	philo->last_meal_time = philo->last_meal_time - philo->global->time_to_eat;
	pthread_mutex_unlock(philo->last_meal);
	//printf("last meal = %d\n", philo->last_meal_time);
	pthread_mutex_unlock(philo->global->forks[(philo->id - philo->id % 2) % philo->global->nb_philo]);
	pthread_mutex_unlock(philo->global->forks [(philo->id - 1 + (philo->id % 2)) % philo->global->nb_philo]);
	return (0);
}

void	*death(void *philo_void)
{
	t_philo *philo;

	philo = (t_philo *)philo_void;
	pthread_mutex_lock(philo->global->message);
	pthread_mutex_unlock(philo->global->message);
	while (1)
	{
		pthread_mutex_lock(philo->last_meal);
		if ((get_timestamp(philo->global) - philo->last_meal_time) > philo->global->time_to_die) // && philo->meal_counter != philo->global->nb_meal_required
		{
			pthread_mutex_unlock(philo->last_meal);
			pthread_mutex_lock(philo->global->death);
			if (philo->global->is_dead == 1)
				return (NULL);
			philo->global->is_dead = 1;
			message(philo, DEAD);
			pthread_mutex_unlock(philo->global->death);
			printf("oui\n");
			return (NULL);
		}
		pthread_mutex_unlock(philo->last_meal);
	}
	//exit(0);
	return (NULL) ;
}

void	*routine(void *philo_void) 
{
	t_philo *philo;
	int		ret;
	
	philo = (t_philo *)philo_void;
	philo->last_meal = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)); // ?
	pthread_mutex_init(philo->last_meal, NULL);
	ret = pthread_create(&philo->death, NULL, (void *)death, philo);
	if (ret != 0)
	{
		printf("death thread error");
		return (NULL);
	}
	pthread_mutex_lock(philo->global->message);
	pthread_mutex_unlock(philo->global->message);
	philo->last_meal_time = get_timestamp(philo->global);
	usleep(2);
	//printf(" last meql %d\n", philo->last_meal_time);
	while (philo->meal_counter < philo->global->nb_meal_required && philo->global->is_dead == 0)
	{	
		if (eat(philo) && philo->global->is_dead == 0)
		{
			pthread_join(philo->death, NULL);
			return (NULL);
		}
		if (ft_sleep(philo) && philo->global->is_dead == 0)
		{
			pthread_join(philo->death, NULL);
			return (NULL);
		}
		if (message(philo, THINK) && philo->global->is_dead == 0)
		{
			pthread_join(philo->death, NULL);
			return (NULL);
		}
		// if (philo->global->is_dead == 1 || philo->meal_counter == philo->global->nb_meal_required)
		// 	return (NULL);
	} 
	pthread_join(philo->death, NULL);
	//exit(0);
	return (NULL);
}

int	init_thread(t_global *global)
{
	int	i;
	int	ret;

	i = 0;
	while (i < global->nb_philo)
	{
		ret = pthread_create(&global->philo[i].thread, NULL, (void *)routine, &global->philo[i]);
		if (ret != 0)
		{
			printf("thread error\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_global	global; //autoriser 0 ms ?
	int			i;

	i = 0;

	if (ac < 5 || ac > 6)
	{
		printf("Wrong numbers of args\n"); 
		return (1);
	}
	init_struct(&global, av);
	if (parsing(&global, av))
		return (1);
	init_philo(&global);
	global.message = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(global.message, NULL);
	global.death = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(global.death, NULL);
	if (create_forks(&global) == 1)
	{
		printf("Mutex error\n");
		return (1);
	}
	pthread_mutex_lock(global.message);
	if (init_thread(&global) == 1)
		return (1);
	ms_sleep(50);
	global.start_time = ft_get_time();
	pthread_mutex_unlock(global.message);
	while (i < global.nb_philo)
		pthread_join(global.philo[i++].thread, NULL);
	//free
	return (0);
}