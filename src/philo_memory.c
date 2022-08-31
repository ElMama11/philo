/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:23:47 by mverger           #+#    #+#             */
/*   Updated: 2022/08/31 18:23:48 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_mutexes(t_main *main)
{
	pthread_mutex_destroy(main->is_dead_mutex);
	free(main->is_dead_mutex);
	pthread_mutex_destroy(main->last_meal_mutex);
	free(main->last_meal_mutex);
	pthread_mutex_destroy(main->meal_counter_mutex);
	free(main->meal_counter_mutex);
	pthread_mutex_destroy(main->message_mutex);
	free(main->message_mutex);
	pthread_mutex_destroy(main->signal_mutex);
	free(main->signal_mutex);
}

void free_forks(t_main *main)
{
	int i = 0;

	while (i < main->args->nb_philo)
	{
		pthread_mutex_destroy(main->forks[i]);
		free(main->forks[i]);
		i++;
	}
	free(main->forks);
}

void free_philos(t_main *main)
{
	int i = 0;

	while (i < main->args->nb_philo)
	{
		free(main->philos[i]);
		i++;
	}
	free(main->philos);
}

void free_memory(t_main *main)
{
	free_mutexes(main);
	free_forks(main);
	free_philos(main);
	free(main->args);
}
