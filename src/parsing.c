/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:04:44 by mverger           #+#    #+#             */
/*   Updated: 2022/04/18 17:41:45 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static int	check_str_in_args(t_global *global, char **av)
{
	if (global->time_to_die == 0)
	{
		if (ft_strncmp("0", av[2], 2) != 0)
		{
			printf("time to die must be a number");
			return (1);
		}
	}
	if (global->time_to_eat == 0)
	{
		if (ft_strncmp("0", av[3], 2) != 0)
		{
			printf("time to eat must be a number");
			return (1);
		}
	}
	if (global->time_to_sleep == 0)
	{
		if (ft_strncmp("0", av[4], 2) != 0)
		{
			printf("time to sleep must be a number");
			return (1);
		}
	}
	return (0);
}

int	parsing(t_global *global, char **av)
{	
	if (check_str_in_args(global, av))
		return(1);
	if (global->nb_philo < 1)
	{
		printf("Number of philo required must be superior to 0\n");
		return (1);
	}
	if (global->time_to_die < 0 || global->time_to_eat < 0 || global->time_to_sleep < 0)
	{
		printf("Timestamps must be positive\n");
		return (1);
	}
	if (av[5] && global->nb_meal_required < 1)
	{
		printf("Number of meal required must be superior to 0\n");
		return (1);
	}
	return (0);
}
