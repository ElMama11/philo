/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:23:22 by mverger           #+#    #+#             */
/*   Updated: 2022/08/31 18:23:25 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void i_must_sleep(t_philo *philo)
{
	if (is_simulation_ended(philo) || is_eatings_completed(philo->main) || is_philo_satisfied(philo))
		return;
	write_something(philo, 3);
	ms_sleep_with_simulation_ended_check(philo->main->args->time_to_sleep, philo);
}

void i_must_think(t_philo *philo)
{
	if (is_simulation_ended(philo) || is_eatings_completed(philo->main) || is_philo_satisfied(philo))
		return;
	write_something(philo, 4);
}

int i_must_eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	process_lastmeal_time(philo);
	write_something(philo, 2);
	pthread_mutex_lock(philo->main->meal_counter_mutex);
	if (philo->meal_counter != -1)
		philo->meal_counter++;
	pthread_mutex_unlock(philo->main->meal_counter_mutex);
	ms_sleep_with_simulation_ended_check(philo->main->args->time_to_eat, philo);
	unlock_forks(philo);
	return (0);
}
