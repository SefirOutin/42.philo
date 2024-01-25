/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:03:19 by soutin            #+#    #+#             */
/*   Updated: 2024/01/25 21:11:28 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_and_fill(t_shared *vars, int c, char **v)
{
	memset(vars, 0, sizeof(t_shared));
	vars->nb_philos = ft_atoi(v[1]);
	vars->time_to_die = ft_atoi(v[2]);
	vars->time_to_eat = ft_atoi(v[3]);
	vars->time_to_sleep = ft_atoi(v[4]);
	if (c == 6)
		vars->notepme = ft_atoi(v[5]);
	else
		vars->notepme = -1;
	if (!vars->nb_philos || !vars->time_to_die || !vars->time_to_eat)
		return (1);
	if (pthread_mutex_init(&vars->m_dead, NULL)
		|| pthread_mutex_init(&vars->m_eat, NULL)
		|| pthread_mutex_init(&vars->m_write, NULL))
		return (1);
	return (0);
}

int	parsing_and_init(t_philo *philos, t_shared *vars, char **v, int c)
{
	int	i;

	i = 0;
	if ((c < 5 || c > 6) || check_digit(v) || check_and_fill(vars, c, v))
		return (1);
	while (i < vars->nb_philos)
	{
		memset(&philos[i], 0, sizeof(t_philo));
		philos[i].id = i + 1;
		philos[i].shared = vars;
		pthread_mutex_init(&philos[i].fork_r, NULL);
		philos[i].start = get_current_time();
		if (i + 1 == philos[0].shared->nb_philos)
			philos[i].fork_l = philos[0].fork_r;
		else
			philos[i].fork_l = philos[i + 1].fork_r;
		i++;
	}
	return (0);
}

void	mutex_write(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->shared->m_write);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&philo->shared->m_write);
}

int	wants_to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_r);
	pthread_mutex_lock(&philo->fork_l);
	pthread_mutex_lock(&philo->shared->m_eat);
	ft_putnbr(philo->id);
	mutex_write(philo, " is eating\n");
	pthread_mutex_unlock(&philo->shared->m_eat);
	pthread_mutex_unlock(&philo->fork_l);
	pthread_mutex_unlock(&philo->fork_r);
	philo->last_time_ate = get_current_time();
	return (0);
}

int	enough_times_eating(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos[0].shared->notepme == -1)
		return (0);
	while (i < philos[0].shared->nb_philos)
	{
		if (philos[i].count_times_eating < philos[i].shared->notepme)
			return (0);
		i++;
	}
	return (1);
}

int	is_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].shared->nb_philos)
	{
		if (get_current_time() >= philos[i].last_time_ate + philos[i].shared->time_to_die)
		{
			pthread_mutex_lock(&philos[i].shared->m_dead);
			philos[i].shared->dead = true;
			pthread_mutex_unlock(&philos[i].shared->m_dead);
			return (1);
		}
	}
	return (0);
}

void	*routine_monitoring(void *arg)
{
	t_philo	*philos;

	philos = arg;
	while (1)
	{
		if (enough_times_eating(philos))
		{
			pthread_mutex_lock(&philos[0].shared->m_dead);
			printf("fini\n");
			philos[0].shared->dead = true;
			pthread_mutex_unlock(&philos[0].shared->m_dead);
		}
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id %2 == 0)
		ft_usleep(1);
	while (!philo->shared->dead)
	{
		printf("ok\n");
		wants_to_eat(philo);
		ft_usleep(philo->shared->time_to_sleep);
		philo->count_times_eating++;
	}
	return (NULL);
}

int	join_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].shared->nb_philos)
	{
		if (pthread_join(philos[i].philo, NULL) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	create_philos(t_philo *philos, t_shared *vars)
{
	int	i;

	i = 0;
	while (i < vars->nb_philos)
	{
		
		if (pthread_create(&philos[i].philo, NULL, routine,
				(void *)&philos[i]) < 0)
			return (1);
		i++;
	}
	if (join_threads(philos))
		return (1);
	return (0);
}

int	main(int c, char **v)
{
	t_philo		philos[200];
	pthread_t	monitor;
	t_shared	vars;

	memset(philos, 0, sizeof(t_philo *) * 200);
	if (!parsing_and_init(philos, &vars, v, c))
	{
		pthread_create(&monitor, NULL, routine_monitoring, (void *)philos);
		create_philos(philos, &vars);
		pthread_join(monitor, NULL);
	}
	else
		printf("error number\n");
	return (0);
}