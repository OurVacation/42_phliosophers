/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_odd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:43:38 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/04 19:10:15 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine_odd(void *arg);

static void	philo_eat_odd(t_philo *philo)
{
	int		i;
	t_ll	time_to_end;

	if (check_if_finished(philo->rule) == 1)
		return ;
	if (philo->rule->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->rule, philo->id, FORK);
		while (check_if_finished(philo->rule) == 0)
			usleep(1000);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_status(philo->rule, philo->id, FORK);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo->rule, philo->id, FORK);

	print_status(philo->rule, philo->id, EAT);

	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_eat_time = get_curtime();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	time_to_end = get_last_eat_time(philo) + philo->rule->time_to_eat;
	i = 0;
	while (i < philo->rule->time_to_eat * 10 && check_if_finished(philo->rule) == 0)
	{
		usleep(100);
		if (get_curtime() >= time_to_end)
			break ;
		i++;
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine_odd(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_if_finished(philo->rule) == 0)
	{
		philo_eat_odd(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
