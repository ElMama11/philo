/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:23:43 by mverger           #+#    #+#             */
/*   Updated: 2022/10/20 16:09:56 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ms_sleep(int time)
{
	int	tv_start;
	int	tv_current;

	tv_start = ft_get_time();
	tv_current = ft_get_time();
	while ((tv_current - tv_start) < time)
	{
		usleep(50);
		tv_current = ft_get_time();
	}
}

int	ms_sleep_with_simulation_ended_check(int time, t_philo *philo)
{
	int	tv_start;
	int	tv_current;

	tv_start = ft_get_time();
	tv_current = ft_get_time();
	while ((tv_current - tv_start) < time)
	{
		usleep(50);
		if (is_simulation_ended(philo) || is_eatings_completed(philo->main))
			return (1);
		tv_current = ft_get_time();
	}
	return (0);
}

int	get_timestamp(t_main *main)
{
	return (ft_get_time() - main->start_time);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	neg;

	neg = 0;
	i = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (neg == 1)
		nb *= -1;
	return (nb);
}
