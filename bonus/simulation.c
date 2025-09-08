/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:24:49 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/09/08 13:25:39 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bouns.h"

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
	int i;

	rule->start_time = get_curtime();
	set_last_eat_time(rule, philo);
	i = 1;
	while(i < rule->num_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			return (perror("Fork failed"), -1);
		else if (philo[i].pid == 0)
		{
			philo_routine(&philo[i]);
			exit(0);
		}
		i += 2;
	}
	usleep(5000);
	i = 0;
	while(i < rule->num_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			return (perror("Fork failed"), -1);
		else if (philo[i].pid == 0)
		{
			philo_routine(&philo[i]);
			exit(0);
		}
		i += 2;
	}
}
