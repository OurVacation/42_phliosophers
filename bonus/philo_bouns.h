/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bouns.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimtaewon <gimtaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 05:09:19 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/09/07 22:22:45 by gimtaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BOUNS_H
# define PHILO_BOUNS_H

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef long long	t_ll;

# define INT_MAX 2147483647
# define INT_MIN -2147483648

#define DIE "died"
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define FORK "has taken a fork"

typedef struct s_philo	t_philo;

typedef struct s_rule
{
	int				num_philos;
	t_ll			time_to_die;
	t_ll			time_to_eat;
	t_ll			time_to_sleep;
	int				must_eat_count;
	t_ll			start_time;
	int				is_finished;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*finish_sem;
}	t_rule;

typedef struct s_philo
{
	pid_t			pid;
	int				id;
	int				eat_count;
	t_ll			last_eat_time;
	t_rule			*rule;
	pthread_t		monitor_thread;
}	t_philo;

//util.c
int		ft_atoll(const char *str, int *num);
void	*ft_calloc(size_t nmemb, size_t size);



//time.c

#endif
