/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:51:17 by mverger           #+#    #+#             */
/*   Updated: 2022/06/22 21:09:48 by mverger          ###   ########.fr       */
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

int message (t_philo *philo, char *message)
{
	if (message == FORK)
		printf(FORK, get_time_in_ms(philo->global), philo->id);
	return (0);
}

int	eat(t_philo *philo)
{
	int	time;
	// pthread_mutex_lock(&((t_global *)philo->global)->forks[philo->left_fork]);
	// pthread_mutex_lock(&((t_global *)philo->global)->forks[philo->right_fork]);
	time = 0;
	pthread_mutex_lock(philo->global->forks[(philo->id - philo->id % 2) % philo->global->nb_philo]);
    if (message(philo, FORK))
        return (1);
    pthread_mutex_lock(philo->global->forks [(philo->id - 1 + (philo->id % 2)) % philo->global->nb_philo]);
    if (message(philo, FORK))
        return (1);
	philo->start_eating = get_time_in_ms(philo->global);
	while (time < philo->global->time_to_eat)
	{
		time = get_time_in_ms(philo->global);
		time = time - philo->start_eating;
	}
	pthread_mutex_unlock(philo->global->forks[(philo->id - philo->id % 2) % philo->global->nb_philo]);
	pthread_mutex_unlock(philo->global->forks [(philo->id - 1 + (philo->id % 2)) % philo->global->nb_philo]);
	return (0);
}

void	death(void *philo_void)
{
	t_philo *philo;

	philo = (t_philo *)philo_void;
	// while (1)
	// {
	// 	if ()
	// }
}

void	routine(void *philo_void) 
{
	t_philo *philo;
	int		ret;
	
	philo = (t_philo *)philo_void;
	ret = pthread_create(&philo->death, NULL, (void *)death, &philo);
	if (ret != 0)
	{
		printf("death thread error");
		return ;
	}
	eat(philo);
	
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
	if (create_forks(&global) == 1)
	{
		printf("Mutex error\n");
		return (1);
	}
	usleep(2000000);
	printf("%d\n", get_time_in_ms(&global));
	usleep(2000000);
	printf("%d\n", get_time_in_ms(&global));
	return (0);
}