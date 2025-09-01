/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:06:01 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/01 11:26:51 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_rule	*rule;
	int		i;
	int		j;
	int		finished_count;

	rule = (t_rule *)arg;
	while (1)
	{
		i = 0;
		while (i < rule->num_philos)
		{
			pthread_mutex_lock(&rule->threads[i].meal_mutex);
			if (get_curtime() - rule->threads[i].last_eat_time >= rule->time_to_die)
			{
				print_status(rule, rule->threads[i].id, DIE);
				set_finished(rule, 1);
				pthread_mutex_unlock(&rule->threads[i].meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&rule->threads[i].meal_mutex);
			if (rule->must_eat_count > 0)
			{
				finished_count = 0;
				j = 0;
				while (j < rule->num_philos)
				{
					pthread_mutex_lock(&rule->threads[j].meal_mutex);
					if (rule->threads[j].eat_count >= rule->must_eat_count)
						finished_count++;
					pthread_mutex_unlock(&rule->threads[j].meal_mutex);
					j++;
				}
				if (finished_count == rule->num_philos)
				{
					set_finished(rule, 1);
					return (NULL);
				}
			}
			i++;
		}
		if (check_if_finished(rule) == 1)
			return (NULL);
		usleep(1500);
	}
	return (NULL);
}
