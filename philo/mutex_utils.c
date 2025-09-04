/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimtaewon <gimtaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:32:28 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/05 02:38:16 by gimtaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_finished(t_rule *rule);
int	set_finished(t_rule *rule, int status);
int	print_status(t_rule *rule, int id, char *status);
t_ll	get_last_eat_time(t_philo *philo);
void	update_eat_time_count(t_philo *philo);

int	is_finished(t_rule *rule)
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
	if (is_finished(rule) == 1 && ft_strncmp(status, DIE, ft_strlen(DIE)) != 0)
	{
		pthread_mutex_unlock(&rule->print_mutex);
		return (1);
	}
	timestamp = get_curtime() - rule->start_time;
	printf("%lld %d %s\n", timestamp, id, status);
	pthread_mutex_unlock(&rule->print_mutex);
	return (0);
}

t_ll	get_last_eat_time(t_philo *philo)
{
	t_ll	last_eat_time;

	pthread_mutex_lock(&philo->meal_mutex);
	last_eat_time = philo->last_eat_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (last_eat_time);
}

void	update_eat_time_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_eat_time = get_curtime();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
}
