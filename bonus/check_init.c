/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:16:42 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/08 15:20:36 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		{
			printf("Error: Invalid argument\n");
			return (-1);
		}
		if (num <= 0)
		{
			printf("Error: Argument must be a positive integer\n");
			return (-1);
		}
		i++;
	}
	return (1);
}
