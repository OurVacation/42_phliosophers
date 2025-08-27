/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:47:13 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/26 16:41:11 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 철학자수, 죽는 시간, 먹는시간, 자는 시간, 각 철학자가 먹어야하는 횟수

int main(int ac, char **av)
{
	t_rule	rule;
	t_philo	*philo;
	pthread_t	monitor_thread;

	if (check_argv(ac, av) < 0)
		return (-1);
	init(&rule, &philo, av);
	rule.threads = philo;
	start_meal(&rule, philo);
	pthread_create(&monitor_thread, NULL, monitor_routine, &rule);
	while (check_if_finished(&rule) == 0)
		usleep(100);
	wait_for_meal_end(&rule, philo, monitor_thread);
	return (0);
}
