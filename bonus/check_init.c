/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:16:42 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/09 11:59:30 by taewonki         ###   ########.fr       */
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
	rule->processes = ft_calloc(rule->num_philos, sizeof(pid_t));
	rule->forks = sem_open(SEM_FORKS, O_CREAT, 0644, rule->num_philos);
	rule->finish_sem = sem_open(SEM_FINISH, O_CREAT, 0644, 1);
	rule->print_sem = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
}

void	init_philo(t_rule *rule, t_philo **philo)
{
	int	i;

	*philo = ft_calloc(rule->num_philos, sizeof(t_philo));
	if (!*philo)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < rule->num_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_eat_time = 0;
		(*philo)[i].rule = rule;
	}
}
