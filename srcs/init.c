/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:47:46 by soutin            #+#    #+#             */
/*   Updated: 2024/01/29 19:01:23 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_digit(char **str)
{
    int i;
    int j;

    i = 1;
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if (!(str[i][j] >= 48 && str[i][j] <= 57))
	    	    return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int	check_and_fill(t_shared *vars, int c, char **v)
{
	memset(vars, 0, sizeof(t_shared));
    vars->start = get_current_time();
	vars->nb_philos = ft_atoi(v[1]);
	vars->time_to_die = ft_atoi(v[2]);
	vars->time_to_eat = ft_atoi(v[3]);
	vars->time_to_sleep = ft_atoi(v[4]);
	vars->notepme = -1;
	if (c == 6)
		vars->notepme = ft_atoi(v[5]);
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
    int start;

	i = 0;
	if ((c < 5 || c > 6) || check_digit(v) || check_and_fill(vars, c, v))
		return (1);
	start = get_current_time();
    while (i < vars->nb_philos)
	{
        // printf("init i : %d nb_philos : %d\n", i, vars->nb_philos);
		memset(&philos[i], 0, sizeof(t_philo));
		philos[i].id = i + 1;
		philos[i].shared = vars;
		philos[i].count_times_eating = 0;
		pthread_mutex_init(&philos[i].fork_r, NULL);
		if (i + 1 == philos[0].shared->nb_philos)
			philos[i].fork_l = &philos[0].fork_r;
		else
			philos[i].fork_l = &philos[i + 1].fork_r;
        philos[i].last_time_ate = get_current_time();
		i++;
	}
	return (0);
}
