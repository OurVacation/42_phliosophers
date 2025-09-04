/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:18:19 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/04 19:13:49 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_eat(t_philo *philo);

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
	int	i;

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
	i = 0;
	while (i < philo->rule->time_to_eat * 10 && check_if_finished(philo->rule) == 0)
	{
		usleep(100);
		i++;
	}

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	int		i;
	t_ll	time_to_end;

	if (check_if_finished(philo->rule) == 1)
		return ;
	print_status(philo->rule, philo->id, SLEEP);
	time_to_end = get_curtime() + philo->rule->time_to_sleep;
	i = 0;
	while (i < philo->rule->time_to_sleep * 10 && check_if_finished(philo->rule) == 0)
	{
		usleep(100);
		if (get_curtime() >= time_to_end)
			break ;
		i++;
	}
}

void	philo_think(t_philo *philo)
{
	t_ll	remained_time;
	t_ll	time_to_do;
	t_ll	time_to_think;

	if (check_if_finished(philo->rule) == 1)
		return ;
	print_status(philo->rule, philo->id, THINK);
	remained_time = get_curtime() - get_last_eat_time(philo);
	time_to_do = philo->rule->time_to_eat + philo->rule->time_to_sleep;
	time_to_think = philo->rule->time_to_die - remained_time - time_to_do;
	if (time_to_think > 0)
	{
		usleep(time_to_think * 2 / 3);
	}
	else
		usleep(100);
}
