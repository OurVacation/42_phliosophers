/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:58:06 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/09 13:53:03 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_last_eat_time(t_rule *rule, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < rule->num_philos)
	{
		philo[i].last_eat_time = rule->start_time;
		i++;
	}
}

void	start_meal(t_rule *rule, t_philo *philo)
{
	int	i;

	rule->start_time = get_curtime();
	set_last_eat_time(rule, philo);
	i = 1;
	while (i < rule->num_philos)
	{
		rule->processes[i] = fork();
		if (rule->processes[i] == 0)
			philo_routine(philo[i]);
	}
	usleep(5000);
	i = 0;
	while (i < rule->num_philos)
	{
		rule->processes[i] = fork();
		if (rule->processes[i] == 0)
			philo_routine(philo[i]);
		i += 2;
	}
}
