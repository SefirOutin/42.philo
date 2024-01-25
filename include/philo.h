/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:57:05 by soutin            #+#    #+#             */
/*   Updated: 2024/01/25 20:58:35 by soutin           ###   ########.fr       */
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
}					t_shared;

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	int				count_times_eating;
	int				last_time_ate;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	fork_r;
	size_t			start;
	t_shared		*shared;
}					t_philo;

int					check_digit(char **str);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);
int	ft_strlen(char *str);
void	ft_putnbr(int nb);

#endif