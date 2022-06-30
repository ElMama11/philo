/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:51:17 by mverger           #+#    #+#             */
/*   Updated: 2022/06/30 18:42:40 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"
//[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]

int message (t_philo *philo, char *message)
{
	if (message == FORK)
		printf(FORK, get_timestamp(philo->global), philo->id);
	else if (message == EAT)
		printf(EAT, get_timestamp(philo->global), philo->id);
	else if (message == SLEEP)
		printf(SLEEP, get_timestamp(philo->global), philo->id);
	else if (message == THINK)
		printf(THINK, get_timestamp(philo->global), philo->id);
	else if (message == DEAD)
	{
		printf(DEAD, get_timestamp(philo->global), philo->id);
		return (1);	
	}
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
	philo->last_meal = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->last_meal, NULL);
	pthread_mutex_lock(philo->global->forks[(philo->id - philo->id % 2) % philo->global->nb_philo]);
    if (message(philo, FORK))
        return (1);
    pthread_mutex_lock(philo->global->forks [(philo->id - 1 + (philo->id % 2)) % philo->global->nb_philo]);
    if (message(philo, FORK))
        return (1);
	pthread_mutex_lock(philo->global->death);
	if (message(philo, EAT))
        return (1);
	philo->meal_counter++;
	ms_sleep(philo->global->time_to_eat);
	pthread_mutex_lock(philo->last_meal);
	philo->last_meal_time = get_timestamp(philo->global);
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
	while (1)
	{
		//printf("ts == %lu\n", get_timestamp(philo->global));
		if ((get_timestamp(philo->global) - philo->last_meal_time) > philo->global->time_to_die && philo->meal_counter != philo->global->nb_meal_required)
		{
			if (philo->global->is_dead == 1)
				return (NULL);
			philo->global->is_dead = 1;
			message(philo, DEAD);
			//printf("oui\n");
			pthread_mutex_unlock(philo->global->death);
			return (NULL);
		}
	}
	//exit(0);
	return (NULL) ;
}

void	*routine(void *philo_void) 
{
	t_philo *philo;
	int		ret;
	
	philo = (t_philo *)philo_void;
	philo->global->death = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->global->message = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->global->message, NULL);
	pthread_mutex_init(philo->global->death, NULL);
	ret = pthread_create(&philo->death, NULL, (void *)death, philo);
	if (ret != 0)
	{
		printf("death thread error");
		return (NULL);
	}
	while (philo->meal_counter < philo->global->nb_meal_required && philo->global->is_dead == 0)
	{	
		pthread_mutex_lock(philo->global->message);
		if (philo->global->is_dead == 1)
			return (NULL);
		if (eat(philo) && philo->global->is_dead == 0)
		{
			pthread_join(philo->death, NULL);
			return (NULL);
		}
		pthread_mutex_unlock(philo->global->message);
		if (philo->global->is_dead == 1)
			break ; // return NULL = tout casser
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
	if (init_thread(&global) == 1)
		return (1);
	if (create_forks(&global) == 1)
	{
		printf("Mutex error\n");
		return (1);
	}
	while (i < global.nb_philo)
		pthread_join(global.philo[i++].thread, NULL);
	//free
	return (0);
}