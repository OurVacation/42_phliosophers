/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:18:19 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/28 15:53:42 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_if_finished(philo->rule) == 0)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->rule, philo->id, FORK);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->rule, philo->id, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->rule, philo->id, FORK);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->rule, philo->id, FORK);
	}

	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_eat_time = get_curtime();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);

	print_status(philo->rule, philo->id, EAT);
	usleep(philo->rule->time_to_eat * 1000);

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo->rule, philo->id, SLEEP);
	usleep(philo->rule->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	print_status(philo->rule, philo->id, THINK);
	usleep(1000);
}
