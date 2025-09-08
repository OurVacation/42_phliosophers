/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bouns.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 05:09:19 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/09/08 13:28:15 by taewonki         ###   ########.fr       */
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

# define DIE "died"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"

# define SEM_FORKS "/sem_forks"
# define SEM_PRINT "/sem_print"
# define SEM_FINISH "/sem_finish"

typedef struct s_philo	t_philo;

typedef struct s_rule
{
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat_count;
	t_ll	start_time;
	int		is_finished;
	pid_t	*philo_pids;
	sem_t	*forks;
	sem_t	*print_sem;
	sem_t	*finish_sem;
}	t_rule;

typedef struct s_philo
{
	pid_t			pid;
	int				id;
	int				eat_count;
	sem_t			*meal_sem;
	t_ll			last_eat_time;
	t_rule			*rule;
	pthread_t		monitor_thread;
}	t_philo;

//util.c
int		ft_atoll(const char *str, int *num);
void	*ft_calloc(size_t nmemb, size_t size);



//time.c

#endif
