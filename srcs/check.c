/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:50:15 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/27 11:32:55 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argv(int ac, char **av)
{
	int	i;
	int	num;

	if (ac < 2 || ac > 6)
		return (-1);
	i = 1;
	while (av[i])
	{
		if (ft_atoll(av[i], &num) < 0)
			return (-1);
		if (num <= 0)
			return (-1);
		i++;
	}
	return (1);
}
