/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:33:49 by soutin            #+#    #+#             */
/*   Updated: 2024/02/15 18:58:30 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	enough_times_eating(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos[0].shared->notepme == -1)
		return (0);
	while (i < philos[0].shared->nb_philos)
	{
		pthread_mutex_lock(&philos[i].shared->m_eat);
		if (philos[i].count_times_eating < philos[i].shared->notepme)
			return (pthread_mutex_unlock(&philos[i].shared->m_eat), 0);
		pthread_mutex_unlock(&philos[i].shared->m_eat);
		i++;
	}
	pthread_mutex_lock(&philos[0].shared->m_dead);
	philos[0].shared->dead = true;
	pthread_mutex_unlock(&philos[0].shared->m_dead);
	return (1);
}

int	is_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].shared->nb_philos)
	{
		pthread_mutex_lock(&philos[0].shared->m_eat);
		if ((get_current_time()
				- philos[i].last_time_ate) >= philos[i].shared->time_to_die)
		{
			pthread_mutex_unlock(&philos[0].shared->m_eat);
			mutex_write(&philos[i], "died");
			return (1);
		}
		pthread_mutex_unlock(&philos[0].shared->m_eat);
		i++;
	}
	return (0);
}

void	*routine_monitoring(void *arg)
{
	t_philo	*philos;

	philos = arg;
	while (1)
	{
		if (is_dead(philos) || enough_times_eating(philos))
			break ;
	}
	return (NULL);
}
