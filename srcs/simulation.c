/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:59:51 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/28 14:15:51 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_meal(t_rule *rule, t_philo *philo)
{
	int i;

	i = 0;
	rule->start_time = get_curtime();
	while (i < rule->num_philos)
	{
		philo[i].last_eat_time = rule->start_time;
		pthread_create(&(philo[i]).thread, NULL, philo_routine, &philo[i]);
		i++;
	}
}

void	wait_for_meal_end(t_rule *rule, t_philo *philo, pthread_t monitor)
{
	int i;

	i = 0;
	while (i < rule->num_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	pthread_mutex_destroy(&rule->print_mutex);
	pthread_mutex_destroy(&rule->finish_mutex);
	i = 0;
	while (i < rule->num_philos)
	{
		pthread_mutex_destroy(&philo[i].meal_mutex);
		pthread_mutex_destroy(&rule->forks[i]);
		i++;
	}
	free(rule->forks);
	free(philo);
}
