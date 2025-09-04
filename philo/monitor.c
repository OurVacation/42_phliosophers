/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimtaewon <gimtaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:06:01 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/05 04:55:01 by gimtaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	count_each_philo_eat(t_rule *rule);
static int	check_is_timeover(t_rule *rule, t_philo *philo);

void	*monitor_routine(void *arg)
{
	t_rule	*rule;
	int		i;

	rule = (t_rule *)arg;
	while (1)
	{
		i = 0;
		while (i < rule->num_philos)
		{
			if (check_is_timeover(rule, &rule->threads[i]) == 1)
				return (NULL);
			if (count_each_philo_eat(rule) == 1)
				return	(NULL);
			i++;
		}
		if (is_finished(rule) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static int	count_each_philo_eat(t_rule *rule)
{
	int	i;
	int	finished_count;

	i = 0;
	finished_count = 0;
	while (i < rule->num_philos)
	{
		pthread_mutex_lock(&rule->threads[i].meal_mutex);
		if (rule->threads[i].eat_count >= rule->must_eat_count)
			finished_count++;
		pthread_mutex_unlock(&rule->threads[i].meal_mutex);
		i++;
	}
	if (finished_count == rule->num_philos)
	{
		set_finished(rule, 1);
		return (1);
	}
	return (0);
}

static int	check_is_timeover(t_rule *rule, t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (get_curtime() - philo->last_eat_time > rule->time_to_die)
	{
		print_status(rule, philo->id, DIE);
		set_finished(rule, 1);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}
