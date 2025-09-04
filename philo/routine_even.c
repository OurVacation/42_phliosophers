/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_even.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimtaewon <gimtaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:36:28 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/05 02:39:10 by gimtaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine_even(void *arg);

static void	philo_eat_even(t_philo *philo)
{
	int		i;
	t_ll	time_to_end;

	if (is_finished(philo->rule) == 1)
		return ;
	if (philo->rule->num_philos == 1)
		return (one_philo(philo));
	pthread_mutex_lock(philo->right_fork);
	print_status(philo->rule, philo->id, FORK);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo->rule, philo->id, FORK);
	print_status(philo->rule, philo->id, EAT);
	update_eat_time_count(philo);
	time_to_end = get_last_eat_time(philo) + philo->rule->time_to_eat;
	i = 0;
	while (i < philo->rule->time_to_eat * 10 && is_finished(philo->rule) == 0)
	{
		usleep(100);
		if (get_curtime() >= time_to_end)
			break ;
		i++;
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine_even(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (is_finished(philo->rule) == 0)
	{
		philo_eat_even(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
