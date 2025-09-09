/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:18:19 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/09 12:53:45 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	one_philo(t_philo *philo);

void	philo_sleep(t_philo *philo)
{
	int		i;
	t_ll	time_to_end;

	if (is_finished(philo->rule) == 1)
		return ;
	print_status(philo->rule, philo->id, SLEEP);
	time_to_end = get_curtime() + philo->rule->time_to_sleep;
	i = 0;
	while (i < philo->rule->time_to_sleep * 10 && is_finished(philo->rule) == 0)
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

	if (is_finished(philo->rule) == 1)
		return ;
	print_status(philo->rule, philo->id, THINK);
	remained_time = get_curtime() - get_last_eat_time(philo);
	time_to_do = philo->rule->time_to_eat + philo->rule->time_to_sleep;
	time_to_think = philo->rule->time_to_die - remained_time - time_to_do;
	if (time_to_think > 0)
	{
		if (time_to_think > philo->rule->time_to_eat * 500)
			time_to_think = philo->rule->time_to_eat * 500;
		usleep(time_to_think * 2 / 3);
	}
	else
		usleep(100);
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo->rule, philo->id, FORK);
	while (is_finished(philo->rule) == 0)
		usleep(1000);
	pthread_mutex_unlock(philo->left_fork);
}
