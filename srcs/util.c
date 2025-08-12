/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:44:51 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/11 16:26:14 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_atoll(const char *str, int *num);
void	*ft_calloc(size_t nmemb, size_t size);

int	ft_atoll(const char *str, int *num)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
		if (sign * result < INT_MIN || sign * result > INT_MAX)
			return (-1);
	}
	if (*str != '\0')
		return (-1);
	*num = (int)(sign * result);
	return (1);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memory;
	size_t	max;
	size_t	area;

	max = (size_t)-1;
	if (size != 0 && nmemb > max / size)
		return (NULL);
	area = nmemb * size;
	memory = malloc(area);
	if (memory != NULL)
		ft_memset(memory, 0, area);
	return (memory);
}
