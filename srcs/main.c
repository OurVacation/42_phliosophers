/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:47:13 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/12 12:00:02 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./phlio 철학자수, 죽는 시간, 먹는시간, 자는 시간, 각 철학자가 먹어야하는 횟수

int main(int ac, char **av)
{
	int 	i;
	t_rule	rule;
	t_philo	phlio[];

	if (check_argv(ac, av) < 0)
		return (-1);
	init_rule(av, &rule);
	i = 0;
	while (i < rule.num_philos)
	{
		pthread_create(&(philo[i]).thread, NULL, philo_routine, &philo[i]);
		i++;
	}

}
