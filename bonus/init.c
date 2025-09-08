/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:17:27 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/09/08 15:09:22 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bouns.h"

void	init_rule(char **av, t_rule *rule)
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
	rule->forks = sem_open(SEM_FORKS, O_CREAT, 0644, rule->num_philos);
	rule->print_sem = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	rule->finish_sem = sem_open(SEM_FINISH, O_CREAT, 0644, 1);
	if (rule->forks == SEM_FAILED || rule->print_sem == SEM_FAILED
		|| rule->finish_sem == SEM_FAILED)
		return (perror("Semaphore initialization failed"), -1);
	return (0);
}

void	init_philo(t_rule *rule, t_philo **philo)
{
	int	i;

	*philo = ft_calloc(rule->num_philos, sizeof(t_philo));
	if (!*philo)
	{
		perror("Failed to allocate memory for philosophers\n"),
		exit(-1);
	}
	i = 0;
	while (i < rule->num_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_eat_time = 0;
		(*philo)[i].rule = rule;
		(*philo)[i].meal_sem = sem_open(SEM_FORKS, O_CREAT, 0644, 1);
		i++;
	}
}
