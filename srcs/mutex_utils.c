/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:32:28 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/01 13:24:08 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_finished(t_rule *rule)
{
	int	finished;

	pthread_mutex_lock(&rule->finish_mutex);
	finished = rule->is_finished;
	pthread_mutex_unlock(&rule->finish_mutex);
	return (finished);
}

int	set_finished(t_rule *rule, int status)
{
	pthread_mutex_lock(&rule->finish_mutex);
	rule->is_finished = status;
	pthread_mutex_unlock(&rule->finish_mutex);
	return (0);
}

int	print_status(t_rule *rule, int id, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&rule->print_mutex);
	if (check_if_finished(rule) == 1 && ft_strncmp(status, DIE, ft_strlen(DIE)) != 0)
	{
		pthread_mutex_unlock(&rule->print_mutex);
		return (1);
	}
	timestamp = get_curtime() - rule->start_time;
	printf("%lld %d %s\n", timestamp, id, status);
	pthread_mutex_unlock(&rule->print_mutex);
	return (0);
}

int judge_to_timeover(t_philo *philo)
{
	long long	time_diff;

	pthread_mutex_lock(&philo->meal_mutex);
	time_diff = get_curtime() - philo->last_eat_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_diff >= philo->rule->time_to_die)
		return (1);
	return (0);
}
