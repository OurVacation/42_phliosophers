/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:06:01 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/12 16:17:12 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			pthread_mutex_lock(&rule->threads[i].set_time_mutex);
			if (get_current_time_ms() - rule->threads[i].last_eat_time
				> rule->time_to_die)
			{
				pthread_mutex_lock(&rule->print_mutex);
				printf("%lld %d has died\n", get_current_time_ms(), rule->threads[i].id);
				pthread_mutex_unlock(&rule->print_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&rule->threads[i].set_time_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
