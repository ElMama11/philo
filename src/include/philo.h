/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 14:55:19 by mverger           #+#    #+#             */
/*   Updated: 2022/04/18 19:13:12 by mverger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>

/* STRUCTS */
typedef struct s_philo {
	int			id;
	int			nb_times_ate;
	pthread_t	thread;
	
}				t_philo;

typedef struct s_global {
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_meal_required;
	t_philo	*philo;
}				t_global;

/* func_libft */
int	ft_atoi(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

/* parsing.c */
int	parsing(t_global *global, char **av);

#endif