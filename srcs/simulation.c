/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:59:51 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/12 16:04:51 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_meal(t_rule *rule, t_philo *philo)
{
	int i;

	i = 0;
	while (i < rule->num_philos)
	{
		pthread_create(&(philo[i]).thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	rule->start_time = get_current_time_ms();
	i = 0;
	while (i < rule->num_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}
