/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:37:11 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/09 11:57:02 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int		is_finished(t_rule *rule);
int		set_finished(t_rule *rule, int status);
int		print_status(t_rule *rule, int id, char *status);
t_ll	get_last_eat_time(t_philo *philo);
void	update_eat_time_count(t_philo *philo);

int	is_finished(t_rule *rule)
{
	int	fin;

	sem_wait(rule->finish_sem);
	fin = rule->is_finished;
	sem_post(rule->finish_sem);
	return (fin);
}

int	set_finished(t_rule *rule, int status)
{
	sem_wait(rule->finish_sem);
	rule->is_finished = status;
	sem_post(rule->finish_sem);
	return (0);
}

int	print_status(t_rule *rule, int id, char *status)
{
	t_ll	timestamp;

	sem_wait(rule->print_sem);
	if (is_finished(rule) == 1 && ft_strncmp(status, DIE, ft_strlen(DIE)) != 0)
	{
		sem_post(rule->print_sem);
		return (1);
	}
	timestamp = get_curtime() - rule->start_time;
	printf("%lld %d %s\n", timestamp, id, status);
	sem_post(rule->print_sem);
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
