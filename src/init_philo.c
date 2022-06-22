/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:14:48 by mverger           #+#    #+#             */
/*   Updated: 2022/06/22 16:00:18 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_global *global)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	global->philo = malloc(sizeof(t_philo) * global->nb_philo + 1);
	if (global->philo == NULL)
		return (1);
	while (j < global->nb_philo)
	{
		global->philo[i].id = i + 1;
		global->philo[i].eat_count = 0;
		global->philo[i].left_fork = i;
		global->philo[i].right_fork = j;
		global->philo[i].start_sleeping = 0;
		global->philo[i].start_eating = 0;
		global->philo[i].global = global;
		i++;
		j++;
	}
	global->philo[i].id = i + 1;
	global->philo[i].eat_count = 0;
	global->philo[i].left_fork = i;
	global->philo[i].right_fork = 0;
	global->philo[i].start_sleeping = 0;
	global->philo[i].start_eating = 0;
	global->philo[i].global = global;
	return (0);
}