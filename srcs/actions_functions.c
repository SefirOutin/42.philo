/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:33:22 by soutin            #+#    #+#             */
/*   Updated: 2024/02/08 18:40:53 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_write(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->shared->m_dead);
	if (philo->shared->dead)
		return (pthread_mutex_unlock(&philo->shared->m_dead), 1);
	pthread_mutex_unlock(&philo->shared->m_dead);
	pthread_mutex_lock(&philo->shared->m_write);
	ft_putnbr((long)(get_current_time() - philo->shared->start));
	write(1, " ", 1);
	ft_putnbr(philo->id);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&philo->shared->m_write);
	return (0);
}

int	wants_to_eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork_r);
		mutex_write(philo, " has taken a fork\n");
		pthread_mutex_lock(philo->fork_l);
	}
	else
	{
		pthread_mutex_lock(philo->fork_l);
		mutex_write(philo, " has taken a fork\n");
		pthread_mutex_lock(&philo->fork_r);
	}
	mutex_write(philo, " has taken a fork\n");
	pthread_mutex_lock(&philo->shared->m_eat);
	mutex_write(philo, " is eating\n");
	philo->last_time_ate = get_current_time();
	philo->count_times_eating++;
	pthread_mutex_unlock(&philo->shared->m_eat);
	ft_usleep(philo->shared->time_to_eat, philo);
	if (philo->id % 2 != 0)
		(pthread_mutex_unlock(philo->fork_l),
			pthread_mutex_unlock(&philo->fork_r));
	else
		(pthread_mutex_unlock(&philo->fork_r),
			pthread_mutex_unlock(philo->fork_l));
	return (0);
}



void	*routine_philos(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo);
	while (1)
	{
		wants_to_eat(philo);
		mutex_write(philo, " is sleeping\n");
		ft_usleep(philo->shared->time_to_sleep, philo);
		mutex_write(philo, " is thinking\n");
		if (philo->shared->notepme > -1)
		{
			pthread_mutex_lock(&philo->shared->m_eat);
			if (philo->count_times_eating == philo->shared->notepme)
				return (pthread_mutex_unlock(&philo->shared->m_eat), NULL);
			pthread_mutex_unlock(&philo->shared->m_eat);
		}
		pthread_mutex_lock(&philo->shared->m_dead);
		if (philo->shared->dead)
			break ;
		pthread_mutex_unlock(&philo->shared->m_dead);
	}
	pthread_mutex_unlock(&philo->shared->m_dead);
	return (NULL);
}
