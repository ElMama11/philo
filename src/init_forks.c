/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:09:05 by mverger           #+#    #+#             */
/*   Updated: 2022/04/24 18:15:10 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_global *global)
{
	int	i;

	global->forks = malloc(sizeof(pthread_mutex_t) * global->nb_philo + 1);
	if (global->forks == NULL)
		return (1);
	i = 0;
	while (i < global->nb_philo)
	{
		if (pthread_mutex_init(&global->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	unlock_forks(t_global *global)
{
	int	i;

	i = 0;
	while (i < global->nb_philo)
	{
		pthread_mutex_unlock(&global->forks[i]);
		i++;
	}
}