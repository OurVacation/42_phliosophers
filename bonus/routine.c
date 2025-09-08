/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimtaewon <gimtaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:25:29 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/09/07 22:25:29 by gimtaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bouns.h"

void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	one_philo(t_philo *philo);

void	philo_sleep(t_philo *philo)
{
	int		i;
	t_ll	time_to_end;

	if (is_finished(philo->rule) == 1)
		return ;
	print_status(philo->rule, philo->id, SLEEP);
	time_to_end = get_curtime() + philo->rule->time_to_sleep;
	i = 0;
	while (i < philo->rule->time_to_sleep * 10 && is_finished(philo->rule) == 0)
	{
		usleep(100);
		if (get_curtime() >= time_to_end)
			break ;
		i++;
	}
}