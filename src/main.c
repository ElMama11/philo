/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:51:17 by mverger           #+#    #+#             */
/*   Updated: 2022/06/19 16:33:22 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	get_time_in_ms(t_global *global)
{
	struct	timeval end;
	unsigned int	temp;
	
	temp = global->start_time.tv_sec * 1000;
	temp = temp + global->start_time.tv_usec / 1000;
	gettimeofday(&end, NULL);
	end.tv_sec *= 1000;
	end.tv_sec += end.tv_usec / 1000;
	return ((end.tv_sec - temp));
}

void	routine(void *philo_void) 
{
	t_philo *philo;

	philo = (t_philo *)philo_void;
	
	//eat global->philo[i].forkL et forkR
	
	//sleep

	//think
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
	t_global global; //autoriser 0 ms ?
	
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
	usleep(2000000);
	printf("%d\n", get_time_in_ms(&global));
	usleep(2000000);
	printf("%d\n", get_time_in_ms(&global));
	return (0);
}