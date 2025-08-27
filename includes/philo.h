/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:44:25 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/27 11:04:28 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_philo	t_philo;

typedef struct s_rule
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				is_finished;
	t_philo			*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	finish_mutex;
	long long		start_time;
}	t_rule;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eat_count;
	long long		last_eat_time;
	t_rule			*rule;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
}	t_philo;

typedef long long	t_ll;

//check.c
int		check_argv(int ac, char **av);

//util.c
int		ft_atoll(const char *str, int *num);
void	*ft_calloc(size_t nmemb, size_t size);

//get_time.c
t_ll	get_curtime(void);

//init.c
void	init_rule(char **av, t_rule *rule);
void	init_philo(t_rule *rule, t_philo **philo);
void	init(t_rule *rule, t_philo **philo, char **av);

//simulation.c
void	start_meal(t_rule *rule, t_philo *philo);
void	wait_for_meal_end(t_rule *rule, t_philo *philo, pthread_t monitor);

//routine.c
void	*philo_routine(void *arg);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

//monitor.c
void	*monitor_routine(void *arg);

//mutex_utils.c
int		check_if_finished(t_rule *rule);

#endif
