/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 15:24:31 by mverger           #+#    #+#             */
/*   Updated: 2022/06/22 15:59:06 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_global *global, char **av)
{
	int	i;

	gettimeofday(&global->start_time, NULL);
	i = 0;
	global->nb_philo = ft_atoi(av[1]);
	global->time_to_die = ft_atoi(av[2]);
	global->time_to_eat = ft_atoi(av[3]);
	global->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		global->nb_meal_required = ft_atoi(av[5]);
	else
		global->nb_meal_required = -1;
	
}