#ifndef PHILO2_H
# define PHILO2_H

# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# define FORK "%d %d has taken a fork\n"
# define SLEEP "%d %d is sleeping\n"
# define THINK "%d %d is thinking\n"
# define DEAD "%d %d died\n"
# define EAT "%d %d is eating\n"

/* STRUCTS */
typedef struct s_args {
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_meal_required;
}					t_args;

typedef struct s_philo {
	int				id;
	int				last_meal_time;
	int				meal_counter;
	struct s_main	*main;
}					t_philo;

typedef struct s_main {
	pthread_t		*threads;
	pthread_mutex_t	**forks;
	t_philo			**philos;
	int				start_time;
	t_args			*args;
}					t_main;

int				parsing(t_main *main, int ac, char **av);
int				create_forks(t_main *main);
int 			create_philo_structs(t_main *main);
void 			*philosophers_routine(void *philo_void);
int				create_philo_threads(t_main *main);
unsigned long	ft_get_time(void);
void			ms_sleep(int time);
int				get_timestamp(t_main *main);
void 			init(t_main *main);

#endif