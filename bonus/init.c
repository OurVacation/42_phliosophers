/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimtaewon <gimtaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:17:27 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/09/07 22:25:15 by gimtaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bouns.h"

int	init_rule(char **av, t_rule *rule)
{
	int i;

	ft_atoll(av[1], &rule->num_philos);
	ft_atoll(av[2], &rule->time_to_die);
	ft_atoll(av[3], &rule->time_to_eat);
	ft_atoll(av[4], &rule->time_to_sleep);
	if (av[5])
		ft_atoll(av[5], &rule->must_eat_count);
	else
		rule->must_eat_count = -1;
	rule->is_finished = 0;
	rule->forks = sem_open("/forks_sem", O_CREAT, 0644, rule->num_philos);
	rule->print_sem = sem_open("/print_sem", O_CREAT, 0644, 1);
	rule->finish_sem = sem_open("/finish_sem", O_CREAT, 0644, 1);
	if (rule->forks == SEM_FAILED || rule->print_sem == SEM_FAILED
		|| rule->finish_sem == SEM_FAILED)
	{
		perror("Semaphore initialization failed");
		return (-1);
	}
	return (0);
}
