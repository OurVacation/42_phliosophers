/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:47:13 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/12 16:04:49 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./phlio 철학자수, 죽는 시간, 먹는시간, 자는 시간, 각 철학자가 먹어야하는 횟수

int main(int ac, char **av)
{
	int 	i;
	t_rule	rule;
	t_philo	phlio[];
	pthread_t	monitor_thread;

	if (check_argv(ac, av) < 0)
		return (-1);
	init_rule(av, &rule);
	init_philo(&rule, &phlio);
	rule.threads = philo;
	start_meal(&rule, phlio);
	pthread_create(&monitor_thread, NULL, monitor_routine, &rule);
}
