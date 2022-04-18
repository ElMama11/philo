/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:51:17 by mverger           #+#    #+#             */
/*   Updated: 2022/04/18 17:36:31 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	init_struct(t_global *global, char **av)
{
	global->nb_philo = ft_atoi(av[1]);
	global->time_to_die = ft_atoi(av[2]);
	global->time_to_eat = ft_atoi(av[3]);
	global->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		global->nb_meal_required = ft_atoi(av[5]);
	printf("%d\n",global->time_to_die );
}

int	main(int ac, char **av)
{
	t_global global; //autoriser 0 ms ?
	
	if (ac < 5 || ac > 6)
	{
		printf("Wrong numbers of args\n");
		return (1);
	}
	init_struct(&global, av);
	if (parsing(&global, av))
		return (1);
	return (0);
}