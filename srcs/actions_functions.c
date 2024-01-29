/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:33:22 by soutin            #+#    #+#             */
/*   Updated: 2024/01/29 19:58:07 by soutin           ###   ########.fr       */
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
	pthread_mutex_lock(&philo->fork_r);
	if (mutex_write(philo, " has taken a fork\n"))
		return (pthread_mutex_unlock(&philo->fork_r), 1);
	pthread_mutex_lock(philo->fork_l);
	if (mutex_write(philo, " has taken a fork\n"))
		return (pthread_mutex_unlock(philo->fork_l),
				pthread_mutex_unlock(&philo->fork_r),
				1);
	mutex_write(philo, " is eating\n");
	pthread_mutex_lock(&philo->shared->m_eat);
	philo->last_time_ate = get_current_time();
	philo->count_times_eating++;
	// printf("id : %d nb ate : %zu\n", philo->id, philo->count_times_eating);
	pthread_mutex_unlock(&philo->shared->m_eat);
	if (ft_usleep(philo->shared->time_to_eat, philo))
		return (1);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(&philo->fork_r);
	return (0);
}

void	*routine_philos(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = arg;
	if (philo->id % 2 == 0)
		ft_usleep(10 , philo);
	while (1)
	{
		pthread_mutex_lock(&philo->shared->m_dead);
		if (philo->shared->dead)
			break ;
		pthread_mutex_unlock(&philo->shared->m_dead);
	// 	// printf("dead ? %d\n", philo->shared->dead);
	// 	// printf("id : %d i : %d\n", philo->id, i);
		i++;
		wants_to_eat(philo);
		mutex_write(philo, " is sleeping\n");
		ft_usleep(philo->shared->time_to_sleep, philo);
		// pthread_mutex_lock(&philo->shared->m_dead);
	}
	printf("11111111111111111111\n");
	// pthread_mutex_unlock(&philo->shared->m_eat);
	return (NULL);
}
