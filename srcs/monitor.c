/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:06:01 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/27 11:05:34 by taewonki         ###   ########.fr       */
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
			// 마지막 식사 시간과 현재 시간 비교
			// 현재 시간 - 마지막 식사 시간 > time_to_die
			// -> 사망 처리
			if (get_current_time_ms() - rule->threads[i].last_eat_time
				> rule->time_to_die)
			// 시간 초과하며 사망 처리
			{
				pthread_mutex_lock(&rule->print_mutex);
				printf("%lld %d has died\n", get_current_time_ms(), rule->threads[i].id);
				pthread_mutex_unlock(&rule->print_mutex);
				pthread_mutex_lock(&rule->finish_mutex);
				rule->is_finished = 1;
				pthread_mutex_unlock(&rule->finish_mutex);
				// rule에 is_finished 플래그 설정
				pthread_mutex_unlock(&rule->threads[i].meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&rule->threads[i].meal_mutex);
/*----------------------------------------------------------------------------*/
			// 모든 철학자가 정해진 횟수 이상 먹었는지 확인
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
					pthread_mutex_lock(&rule->finish_mutex);
					rule->is_finished = 1;
					pthread_mutex_unlock(&rule->finish_mutex);
					return (NULL);
				}
			}
			i++;
		}
		if (check_if_finished(rule) == 1)
			return (NULL);
		usleep(800);
	}
	return (NULL);
}
