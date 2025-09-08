/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:25:29 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/09/08 15:07:21 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bouns.h"

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
		usleep(time_to_think / 2);
	else
		usleep(100);
}

void	one_philo(t_philo *philo)
{
	sem_wait(philo->rule->forks);
	print_status(philo->rule, philo->id, FORK);
	while (is_finished(philo->rule) == 0)
		usleep(100);
	sem_post(philo->rule->forks);
}

void	philo_eat(t_philo *philo)
{
	int		i;
	t_ll	time_to_end;

	if (is_finished(philo->rule) == 1)
		return ;
	if (philo->rule->num_philos == 1)
		return (one_philo(philo));
	sem_wait(philo->rule->forks);
	print_status(philo->rule, philo->id, FORK);
	sem_wait(philo->rule->forks);
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
	sem_post(philo->rule->forks);
	sem_post(philo->rule->forks);
}
