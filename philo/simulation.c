/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:59:51 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/09 15:22:12 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (i < rule->num_philos)
	{
		pthread_create(&(philo[i]).thread, NULL, philo_routine_odd, &philo[i]);
		i += 2;
	}
	usleep(5000);
	i = 0;
	while (i < rule->num_philos)
	{
		pthread_create(&(philo[i]).thread, NULL, philo_routine_even, &philo[i]);
		i += 2;
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
