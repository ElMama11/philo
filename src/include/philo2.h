#ifndef PHILO2_H
#define PHILO2_H

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

#define MAX_THREADS_ALLOWED 256

#define FORK "%d %d has taken a fork.\n"
#define SLEEP "%d %d is sleeping.\n"
#define THINK "%d %d is thinking.\n"
#define DEAD "%d %d died.\n"
#define EAT "%d %d is eating.\n"

/* STRUCTS */
typedef struct s_args
{
	int nb_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_meal_required;
} t_args;

typedef struct s_philo
{
	int id;
	int last_meal_time;
	int meal_counter;
	struct s_main *main;
} t_philo;

typedef struct s_main
{
	pthread_t threads[MAX_THREADS_ALLOWED];
	pthread_mutex_t **forks;
	pthread_mutex_t *is_dead_mutex;
	pthread_mutex_t *last_meal_mutex;
	pthread_mutex_t *message_mutex;
	pthread_mutex_t *signal_mutex;
	pthread_mutex_t *meal_counter_mutex;
	t_philo **philos;
	int start_time;
	int is_dead;
	t_args *args;
} t_main;

/* toto_actions.c */
void i_must_sleep(t_philo *philo);
void i_must_think(t_philo *philo);
int i_must_eat(t_philo *philo);

/* toto_actions_utils.c */
int is_simulation_ended(t_philo *philo);
void lock_forks(t_philo *philo);
void unlock_forks(t_philo *philo);
int take_forks(t_philo *philo);
void process_lastmeal_time(t_philo *philo);
int is_philo_satisfied(t_philo *philo);

/* toto_init.c */
void init(t_main *main);

/* toto_parsing.c */
int parsing(t_main *main, int ac, char **av);

/* toto_time.c */
unsigned long ft_get_time(void);
void ms_sleep(int time);
int get_timestamp(t_main *main);
int ms_sleep_with_simulation_ended_check(int time, t_philo *philo);

/* toto_main.c */
void *philosophers_routine(void *philo_void);
void write_something(t_philo *philo, int message);
int is_philo_dead(t_philo *philo);

/* toto_memory.c */
void free_memory(t_main *main);

/* toto_death.c */
void check_lock_isdead_variable(t_philo *philo);
int is_philo_dead(t_philo *philo);
void join_all_threads(t_main *main);
void wait_until_end(t_main *main);
int is_eatings_completed(t_main *main);
#endif
