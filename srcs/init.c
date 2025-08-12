/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:01:46 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/12 14:45:58 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_rule(char **av, t_rule *rule)
{
	int	i;

	ft_atoll(av[1], &rule->num_philos);
	ft_atoll(av[2], &rule->time_to_die);
	ft_atoll(av[3], &rule->time_to_eat);
	ft_atoll(av[4], &rule->time_to_sleep);
	if (av[5])
		ft_atoll(av[5], &rule->must_eat_count);
	rule->forks = ft_calloc(rule->num_philos, sizeof(pthread_mutex_t));
	if (!rule->forks)
	{
		perror("Failed to allocate memory for forks");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < rule->num_philos)
	{
		pthread_mutex_init(&rule->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&rule->print_mutex, NULL);
}

void	init_philo(t_rule *rule, t_phlio **philo)
{
	int	i;

	*philo = ft_calloc(rule->num_philos, sizeof(t_phlio));
	if (!*philo)
	{
		perror("Failed to allocate memory for philosophers\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < rule->num_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_eat_time = 0;
		(*philo)[i].rule = rule;
		(*philo)[i].left_fork = &rule->forks[i];
		(*philo)[i].right_fork = &rule->forks[(i + 1) % rule->num_philos];
		i++;
	}
}

void	init(t_rule *rule, t_phlio **philo, char **av)
{
	init_rule(av, rule);
	init_philo(rule, philo);
	rule->start_time = get_current_time_ms();
}

void	execute_philo(t_phlio *philo)
{
	int	i;

	i = 0;
	while (i < philo->rule->num_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]) != 0)
		{
			perror("Failed to create philosopher thread");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	philo->rule->start_time = get_current_time_ms();
	i = 0;
	while (i < philo->rule->num_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}
