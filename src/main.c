/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:51:17 by mverger           #+#    #+#             */
/*   Updated: 2022/04/25 18:15:21 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	eat(t_global *global)
{
	struct	timeval start;
	struct	timeval end;
	int		i;
	
	i = 0;
	gettimeofday(&start, NULL);
	while (i < global->nb_philo)
	{
		
		i++;
	}
}

void	routine(void *global) //type void en arg 
{
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
		ret = pthread_create(&global->philo[i].thread, NULL, (void *)routine, (void *)global);
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
		
// 	struct timeval start, end;
// 	gettimeofday(&start, NULL);
// 	 for (int i = 0; i <1e5 ; i++) {
//   }
 
//   gettimeofday(&end, NULL);
//   printf("Time taken to count to 10^5 is : %ld micro seconds\n", end.tv_usec - start.tv_usec);
	return (0);
}