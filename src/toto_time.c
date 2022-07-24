#include "philo2.h"

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

int	get_timestamp(t_main *main)
{
	struct	timeval end;

	return ((ft_get_time() - main->start_time));
}