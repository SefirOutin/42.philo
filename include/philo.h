/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:57:05 by soutin            #+#    #+#             */
/*   Updated: 2024/01/23 19:48:48 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <ctype.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				notepme;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	fork_r;
	size_t			start;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	write_lock;
}					t_philo;

typedef struct	s_actions
{
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	write_lock;
	bool			dead;
}					t_actions;

int					check_digit(char **str);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);

#endif