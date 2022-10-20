/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:23:22 by mverger           #+#    #+#             */
/*   Updated: 2022/10/20 16:18:39 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_something(t_philo *philo, int message)
{
	if (!is_simulation_ended(philo) && !is_eatings_completed(philo->main))
	{
		pthread_mutex_lock(philo->main->message_mutex);
		if (message == 1)
			printf(FORK, get_timestamp(philo->main), philo->id);
		else if (message == 2)
			printf(EAT, get_timestamp(philo->main), philo->id);
		else if (message == 3)
			printf(SLEEP, get_timestamp(philo->main), philo->id);
		else if (message == 4)
			printf(THINK, get_timestamp(philo->main), philo->id);
		pthread_mutex_unlock(philo->main->message_mutex);
	}
	if (message == 5)
	{
		pthread_mutex_lock(philo->main->message_mutex);
		pthread_mutex_lock(philo->main->meal_counter_mutex);
		printf(DEAD, get_timestamp(philo->main), philo->id);
		pthread_mutex_unlock(philo->main->meal_counter_mutex);
		pthread_mutex_unlock(philo->main->message_mutex);
	}
}

void	i_must_sleep(t_philo *philo)
{
	if (is_simulation_ended(philo) || is_eatings_completed(philo->main)
		|| is_philo_satisfied(philo))
		return ;
	write_something(philo, 3);
	ms_sleep_with_simulation_ended_check
	(philo->main->args->time_to_sleep, philo);
}

void	i_must_think(t_philo *philo)
{
	if (is_simulation_ended(philo) || is_eatings_completed(philo->main)
		|| is_philo_satisfied(philo))
		return ;
	write_something(philo, 4);
}

int	i_must_eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	process_lastmeal_time(philo);
	write_something(philo, 2);
	pthread_mutex_lock(philo->main->meal_counter_mutex);
	if (philo->meal_counter != -1)
		philo->meal_counter++;
	pthread_mutex_unlock(philo->main->meal_counter_mutex);
	ms_sleep_with_simulation_ended_check
		(philo->main->args->time_to_eat, philo);
	unlock_forks(philo);
	return (0);
}

void	join_all_threads(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->args->nb_philo)
	{
		pthread_join(main->threads[i], NULL);
		i++;
	}
	return ;
}
