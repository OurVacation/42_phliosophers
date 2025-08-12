/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:18:19 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/12 14:41:11 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	long long	cur_time;

	philo = (t_philo *)arg;
	while (1)
	{








		pthread_mutex_lock(philo->rule->print_mutex);
		printf("%lld %d is sleeping\n", get_current_time_ms(), philo->id);
		pthread_mutex_unlock(philo->rule->print_mutex);
		usleep(philo->rule->time_to_sleep * 1000);

		pthread_mutex_lock(philo->rule->print_mutex);
		printf("%lld %d is thinking\n", get_current_time_ms(), philo->id);
		pthread_mutex_unlock(philo->rule->print_mutex);
	}
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);

	pthread_mutex_lock(philo->rule->print_mutex);
	printf("%lld %d has taken the left fork\n",get_current_time_ms() philo->id);
	pthread_mutex_unlock(philo->rule->print_mutex);

	pthread_mutex_lock(philo->right_fork);

	pthread_mutex_lock(philo->rule->print_mutex);
	printf("%lld %d has taken the right fork\n",get_current_time_ms() philo->id);
	pthread_mutex_lock(philo->rule->print_mutex);

	philo->last_eat_time = get_current_time();
	philo->eat_count++;

	pthread_mutex_lock(philo->rule->print_mutex);
	printf("%lld %d is eating\n", get_current_time_ms(), philo->id);
	pthread_mutex_unlock(philo->rule->print_mutex);

	usleep(philo->rule->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
