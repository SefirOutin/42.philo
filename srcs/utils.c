/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:46:11 by soutin            #+#    #+#             */
/*   Updated: 2024/01/29 19:55:14 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		usleep(500);
		pthread_mutex_lock(&philo->shared->m_dead);
	}
	pthread_mutex_unlock(&philo->shared->m_dead);
	if (philo->shared->dead)
		return (1);
	return (0);
}

void	ft_putnbr(long nb)
{
	long	c;
	
	if (nb < 0)
	{
		write(1, "-", 1);
		ft_putnbr(-nb);
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	c = 48 + nb % 10;
	write(1, &c, 1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}