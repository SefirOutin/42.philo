/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:46:11 by soutin            #+#    #+#             */
/*   Updated: 2024/01/23 18:49:11 by soutin           ###   ########.fr       */
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

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
