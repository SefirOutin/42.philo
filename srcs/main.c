/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:03:19 by soutin            #+#    #+#             */
/*   Updated: 2024/01/23 19:56:25 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing_and_init(t_philo *philos, char **v, int c)
{
	int	nb_philos;
	int	i;

	if ((c < 5 || c > 6) || check_digit(v))
		return (-1);
	nb_philos = ft_atoi(v[1]);
	while (i < nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].nb_philos = nb_philos;
		philos[i].time_to_die = ft_atoi(v[2]);
		philos[i].time_to_eat = ft_atoi(v[3]);
		philos[i].time_to_sleep = ft_atoi(v[4]);
		if (c == 6)
			philos[i].notepme = ft_atoi(v[5]);
		pthread_mutex_init(&philos[i].fork_r, NULL);
		philos[i].start =
			i++;
	}
}

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = philos;
	return (NULL);
}

int	create_philos(t_philo *philos, t_actions *vars)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&vars->dead_lock, NULL)
			|| pthread_mutex_init(&vars->eat_lock, NULL)
			|| pthread_mutex_init(&vars->write_lock, NULL))
			return (1);
	while (i < philos[0].nb_philos)
	{
		if (i + 1 == philos[0].nb_philos)
			philos[i].fqork_l = philos[0].fork_r;
		else
			philos[i].fork_l = philos[i + 1].fork_r;
		if (pthread_create(&philos[i].philo, NULL, routine, (void *)&philos[i]) < 0);
			return (1);
		i++;
	}
	i = 0;
	while (i < philos[0].nb_philos)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
	return (0);
}

int	main(int c, char **v)
{
	t_philo 	philos[200];
	t_actions	vars;

	memset(philos, 0, sizeof(t_philo *) * 200);
	if (parsing_and_init(philos, v, c) < 0)
		printf("error number\n");
	create_philos(philos, &vars);
	return (0);
}