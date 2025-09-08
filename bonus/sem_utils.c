/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 05:33:22 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/09/08 13:28:18 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bouns.h"

int		is_finished(t_rule *rule);
int		set_finished(t_rule *rule, int status);
int		print_status(t_rule *rule, int id, char *status);
t_ll	get_last_eat_time(t_philo *philo);
void	update_eat_time_count(t_philo *philo);

int	is_finished(t_rule *rule)
{
	int	finished;

	sem_wait(rule->finish_sem);
	finished = rule->is_finished;
	sem_post(rule->finish_sem);
	return (finished);
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
	long long	timestamp;

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

	sem_wait(philo->meal_sem);
	last_eat_time = philo->last_eat_time;
	sem_post(philo->meal_sem);
	return (last_eat_time);
}

void	update_eat_time_count(t_philo *philo)
{
	sem_wait(philo->meal_sem);
	philo->last_eat_time = get_curtime();
	philo->eat_count++;
	sem_post(philo->meal_sem);
}
