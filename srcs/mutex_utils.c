/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:32:28 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/26 14:32:56 by taewonki         ###   ########.fr       */
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
