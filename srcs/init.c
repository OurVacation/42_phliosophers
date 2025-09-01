/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:01:46 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/28 15:53:16 by taewonki         ###   ########.fr       */
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
	else
		rule->must_eat_count = -1;
	rule->is_finished = 0;
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
	pthread_mutex_init(&rule->finish_mutex, NULL);
	pthread_mutex_init(&rule->print_mutex, NULL);
}

void	philo_status(t_philo *philo)
{
	printf("Philosopher %d status:\n", philo->id);
	printf("  Eat count: %d\n", philo->eat_count);
	printf("  Last eat time: %lld\n", philo->last_eat_time);
	printf("  Left fork address: %p\n", (void *)philo->left_fork);
	printf("  Right fork address: %p\n", (void *)philo->right_fork);
	printf("  Rule struct address: %p\n", (void *)philo->rule);
}

void	init_philo(t_rule *rule, t_philo **philo)
{
	int	i;

	*philo = ft_calloc(rule->num_philos, sizeof(t_philo));
	if (!*philo)
	{
		perror("Failed to allocate memory for philosophers\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < rule->num_philos)
	{
		printf("Initializing philosopher %d\n", i + 1);
		(*philo)[i].id = i + 1;
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_eat_time = 0;
		(*philo)[i].rule = rule;
		(*philo)[i].left_fork = &rule->forks[i];
		(*philo)[i].right_fork = &rule->forks[(i + 1) % rule->num_philos];
		pthread_mutex_init(&(*philo)[i].meal_mutex, NULL);
		philo_status(&(*philo)[i]);
		printf("----------------------------------------------------\n");
		i++;
	}
}

void	init(t_rule *rule, t_philo **philo, char **av)
{
	init_rule(av, rule);
	init_philo(rule, philo);
}
