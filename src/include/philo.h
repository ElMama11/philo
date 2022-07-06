/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 14:55:19 by mverger           #+#    #+#             */
/*   Updated: 2022/07/06 18:00:46 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
 
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK "%d %d has taken a fork\n"
# define SLEEP "%d %d is sleeping\n"
# define THINK "%d %d is thinking\n"
# define DEAD "%d %d died\n"
# define EAT "%d %d is eating\n"

/* STRUCTS */

typedef struct s_philo {
	int			id;
	int			left_fork;
	int			right_fork;
	int			start_sleeping;
	int			start_eating;
	int			last_meal_time;
	int			meal_counter;
	pthread_mutex_t	*last_meal;
	pthread_t	thread;
	pthread_t	death;
	struct s_global		*global;
	
}				t_philo;

typedef struct s_global {
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal_required;
	int				is_dead;
	long long		start_time;
	pthread_mutex_t	*message;
	pthread_mutex_t	*death;
	pthread_mutex_t	**forks;
	t_philo			*philo;
}				t_global;

/* func_libft */
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* parsing.c */
int		parsing(t_global *global, char **av);

/* init_philo.c */
int		init_philo(t_global *global);

/* init_struct.c */
void	init_struct(t_global *global, char **av);

/* init_forks.c */
int		create_forks(t_global *global);
void	unlock_forks(t_global *global);

/* philo_utils.c */
unsigned long		ft_get_time(void);
void	ms_sleep(int time);
int		get_timestamp(t_global *global);
#endif