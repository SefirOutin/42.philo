/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:46:11 by soutin            #+#    #+#             */
/*   Updated: 2024/02/15 19:00:54 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*d;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	d = malloc((nmemb) * size);
	if (!d)
		return (NULL);
	memset(d, 0, nmemb * size);
	return (d);
}

int	ft_atoi(const char *nptr)
{
	int	number;
	int	sign;
	int	nbs;

	nbs = 0;
	number = 0;
	sign = 1;
	while ((*nptr > 8 && *nptr <= 13) || *nptr == 32)
		nptr++;
	while (*nptr == 45 || *nptr == 43)
	{
		if (*nptr == 45)
			sign *= -1;
		nbs++;
		nptr++;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		number = number * 10 + (*nptr - 48);
		nptr++;
	}
	if (nbs > 1)
		return (0);
	return (number * sign);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	pthread_mutex_lock(&philo->shared->m_dead);
	while ((get_current_time() - start) < milliseconds && !philo->shared->dead)
	{
		pthread_mutex_unlock(&philo->shared->m_dead);
		usleep(1000);
		pthread_mutex_lock(&philo->shared->m_dead);
	}
	pthread_mutex_unlock(&philo->shared->m_dead);
	return (0);
}
