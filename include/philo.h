/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:57:05 by soutin            #+#    #+#             */
/*   Updated: 2024/01/29 19:01:03 by soutin           ###   ########.fr       */
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

typedef struct s_shared
{
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_write;
	bool			dead;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				notepme;
	size_t			start;
}					t_shared;

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	size_t			count_times_eating;
	size_t			last_time_ate;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	fork_r;
	t_shared		*shared;
}					t_philo;

int					check_digit(char **str);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds, t_philo *philos);
int					ft_strlen(char *str);
void				ft_putnbr(long nb);

int					parsing_and_init(t_philo *philos, t_shared *vars, char **v,
						int c);

void				*routine_monitoring(void *arg);
void				*routine_philos(void *arg);

int					mutex_write(t_philo *philo, char *str);
int					wants_to_eat(t_philo *philo);

#endif