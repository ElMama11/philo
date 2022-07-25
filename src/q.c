/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthibaul <jthibaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:17:53 by jthibaul          #+#    #+#             */
/*   Updated: 2022/06/25 15:03:11 by jthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

//2(nb) 800(time to die) 200 (time to eat) 200 (time to sleep) 2 (nb of meal)


int	ft_time_since_start(t_data *data)
{
	return (ft_get_time() - data->ms_init);
}

int	message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex_death);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex_death);
		return (1);
	}
	pthread_mutex_lock(&philo->data->meal_counter);
	if (philo->meal_counter >= philo->data->number_of_time_philosopher_must_eat)
	{
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->meal_counter);
		pthread_mutex_unlock(&philo->data->mutex_death);	
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_death);
	pthread_mutex_unlock(&philo->data->meal_counter);
	pthread_mutex_lock(&philo->data->message);
	ft_printf("%i %i %s", ft_time_since_start(philo->data), philo->philo_nb, str);
	pthread_mutex_unlock(&philo->data->message);
	return (0);
}

void	*death(void	*ptr)
{
	t_philo *philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	pthread_mutex_lock(&data->message);
	pthread_mutex_unlock(&data->message);
	msleep(data->time_to_die / 2);
	while (1)
	{
		pthread_mutex_lock(&data->mutex_death);
		pthread_mutex_lock(&philo->mutex_last_meal);
		//printf("time dead %u\n", philo->ms_last_meal - ft_get_time());
		if (philo->ms_last_meal + data->time_to_die < ft_get_time() || data->dead == 1)
		{
			pthread_mutex_unlock(&philo->mutex_last_meal);
			if (data->dead == 0)
			{
				data->dead = 1;
				pthread_mutex_lock(&philo->data->message);
				ft_printf("%i %i died\n",ft_time_since_start(philo->data), philo->philo_nb);
				pthread_mutex_unlock(&philo->data->message);
				pthread_mutex_unlock(&data->mutex_death);
				return (NULL);
			}
			else
			{
				pthread_mutex_unlock(&data->mutex_death);
				return (NULL);
			}
		}
		pthread_mutex_unlock(&philo->mutex_last_meal);
		pthread_mutex_unlock(&data->mutex_death);
		//msleep(5);
	}
	return (NULL);
}

int	ft_take_fork_and_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[(philo->philo_nb - philo->philo_nb % 2) % philo->data->philo_total]);
	if (message(philo, FORK))
		return (1);
	pthread_mutex_lock(&philo->data->fork[(philo->philo_nb - 1 + (philo->philo_nb % 2)) % philo->data->philo_total]);
	if (message(philo, FORK))
		return (1);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->ms_last_meal += philo->data->time_to_eat;
	pthread_mutex_unlock(&philo->mutex_last_meal);
	if (message(philo, EAT))
		return (1);
	philo->meal_counter++;
	msleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->ms_last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	pthread_mutex_unlock(&philo->data->fork[philo->philo_nb - 1]);
	pthread_mutex_unlock(&philo->data->fork[philo->philo_nb % philo->data->philo_total]);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (message(philo, SLEEP))
		return (1);
	msleep(philo->data->time_to_sleep);
	return (0);
}

void	*ft_routine(void *ptr)
{
	t_philo *philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	printf("philo %d start\n", philo->philo_nb);
	pthread_create(&philo->death, NULL, &death, philo);//verif si ca marche avec le return
	pthread_mutex_lock(&data->message);
	pthread_mutex_unlock(&data->message);
	philo->ms_last_meal = ft_get_time();
	while (1)
	{
		if (ft_take_fork_and_eat(philo))
		{
			pthread_join(philo->death, NULL);
			return (NULL);
		}
		if (ft_sleep(philo))
		{
			pthread_join(philo->death, NULL);
			return (NULL);
		}
		if (message(philo, THINK))
		{
			pthread_join(philo->death, NULL);
			return (NULL);
		}
	}
	pthread_join(philo->death, NULL);
	return (NULL);
}

int main(int ac, char **av)
{
	t_philo		philo_one;
	t_philo		philo_two;
	t_data		data;

	if (parsing(ac, av, &data))
		return (0);
	fill_philo(ac, av, &data);
	pthread_mutex_lock(&data.message);
	pthread_create(&philo_one.thread, NULL, &ft_routine, &philo_one); //verif si ca marche avec le return
	msleep(200);
	pthread_create(&philo_two.thread, NULL, &ft_routine, &philo_two);
	msleep(200);
	pthread_mutex_unlock(&data.message);
	data.ms_init = ft_get_time();
	pthread_join(philo_one.thread, NULL);
	pthread_join(philo_two.thread, NULL); //comment faire avec une tableau de thread?
	free_all(&data);
	printf("end\n");
	return(0);
}