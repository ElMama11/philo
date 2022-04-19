/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:14:48 by mverger           #+#    #+#             */
/*   Updated: 2022/04/19 20:15:23 by mverger          ###   ########.fr       */
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
		i++;
		j++;
		
	}
	global->philo[i].id = i + 1;
	global->philo[i].eat_count = 0;
	global->philo[i].left_fork = i;
	global->philo[i].right_fork = 0;
	return (0);
}