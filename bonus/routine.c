/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:33:17 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/09 13:20:56 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int		philo_routine(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	one_philo(t_philo *philo);

int	philo_routine(t_philo *philo)
{
	pthread_t	monitor;

	pthread_mutex_init(&philo->meal_mutex, NULL);
	pthread_create(&monitor, NULL, monitor_routine, &philo->rule);
	while (is_finished(philo->rule) == 0)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (0);
}

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
			break;
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

void	philo_eat(t_philo *philo)
{
	int		i;
	t_ll	time_to_end;

	if (is_finished(philo->rule) == 1)
		return ;
	if (philo->rule->num_philos == 1)
		return (one_philo);
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

void	one_philo(t_philo *philo)
{
	sem_wait(philo->rule->forks);
	print_status(philo->rule, 1, FORK);
	while (is_finished(philo->rule) == 0)
		usleep(1000);
	sem_post(philo->rule->forks);
}
