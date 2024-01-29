/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:03:19 by soutin            #+#    #+#             */
/*   Updated: 2024/01/29 19:28:22 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].shared->nb_philos)
	{
		// printf("la\n");
		if (pthread_join(philos[i].philo, NULL) < 0)
		{
			printf("ookokokokokokok\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].shared->nb_philos)
	{
		if (pthread_create(&philos[i].philo, NULL, routine_philos,
				(void *)&philos[i]) < 0)
			return (1);
		i++;
	}
	// printf("la--------------\n\n\n\n\n\n");
	if (join_threads(philos))
		return (1);
	return (0);
}

void	destroy(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].shared->nb_philos)
	{
		pthread_mutex_destroy(&philos[i].fork_r);
		i++;
	}
	pthread_mutex_destroy(&philos[0].shared->m_dead);
	pthread_mutex_destroy(&philos[0].shared->m_eat);
	pthread_mutex_destroy(&philos[0].shared->m_write);

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
		create_philos(philos);
		// printf("la\n");
		if (pthread_join(monitor, NULL) < 0)
			printf("ok1111111\n");
		destroy(philos);	
	}
	else
		printf("error number\n");
	return (0);
}