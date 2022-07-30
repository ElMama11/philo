#include "philo2.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		if (str1[i] != str2[i])
			return ((str1[i] - str2[i]));
		i++;
	}
	return (0);
}

static int	check_str_in_args(t_args *args, char **av)
{
	if (args->time_to_die == 0)
	{
		if (ft_strncmp("0", av[2], 2) != 0)
		{
			printf("time to die must be a number");
			return (1);
		}
	}
	if (args->time_to_eat == 0)
	{
		if (ft_strncmp("0", av[3], 2) != 0)
		{
			printf("time to eat must be a number");
			return (1);
		}
	}
	if (args->time_to_sleep == 0)
	{
		if (ft_strncmp("0", av[4], 2) != 0)
		{
			printf("time to sleep must be a number");
			return (1);
		}
	}
	return (0);
}

static int is_input_errors(t_args *args, char **av)
{
	if (check_str_in_args(args, av))
		return(1);
	if (args->nb_philo < 1)
	{
		printf("Number of philo required must be superior to 0\n");
		return (1);
	
	}
	if (args->time_to_die < 0 || args->time_to_eat < 0 || args->time_to_sleep < 0)
	{
		printf("Timestamps must be positive\n");
		return (1);
	}
	if (av[5] && args->nb_meal_required < 1)
	{
		printf("Number of meal required must be superior to 0\n");
		return (1);
	}
	return (0);
}

int	parsing(t_main *main, int ac, char **av)
{
	main->args = (t_args*)malloc(sizeof(t_args));
	memset(main->args, 0, sizeof(t_args));

	if (ac == 5 || ac == 6)
	{
		main->args->nb_philo = atoi(av[1]);
		main->args->time_to_die = atoi(av[2]);
		main->args->time_to_eat = atoi(av[3]);
		main->args->time_to_sleep = atoi(av[4]);
		if (ac == 6)
			main->args->nb_meal_required = atoi(av[5]);
		else
			main->args->nb_meal_required = -1;
		if (is_input_errors(main->args, av))
			return 1;
		return (0);
	}
	printf("Usage: number_of_philosophers time_to_die time_to_eat time_to_sleep [nb_meal_required]");
	return (1);
}