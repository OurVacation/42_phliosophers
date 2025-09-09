/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:13:39 by taewonki          #+#    #+#             */
/*   Updated: 2025/09/08 15:29:50 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIE "died"

# define SEM_FORKS "/sem_forks"
# define SEM_PRINT "/sem_print"
# define SEM_FINISH "/sem_finish"

typedef struct s_philo	t_philo;

typedef long long	t_ll;

typedef struct s_rule
{
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat_count;
	int		is_finished;
	pid_t	*processes;
	sem_t	*forks;
	sem_t	*print_mutex;
	sem_t	*finish_mutex;
	t_ll	start_time;
}	t_rule;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	t_ll			last_eat_time;
	pthread_mutex_t	meal_mutex;
	t_rule			*rule;
}	t_philo;

//utils.c
int		ft_atoll(const char *str, int *num);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);

#endif
