/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:58:30 by mverger           #+#    #+#             */
/*   Updated: 2022/06/27 20:31:38 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

unsigned long	ft_get_time(void)
{
    struct timeval  tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ms_sleep(int time)
{
    int     tv_start;
    int     tv_current;
    tv_start = ft_get_time();
    tv_current = ft_get_time();
    while ((tv_current - tv_start) < time)
    {
        usleep(10);
        tv_current = ft_get_time();
    }
}

unsigned long	get_timestamp(t_global *global)
{
	struct	timeval end;

	//printf(" %lld \n", global->start_time);
	return ((ft_get_time() - global->start_time));
}
