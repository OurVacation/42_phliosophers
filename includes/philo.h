/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:44:25 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/12 15:02:36 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHLIO_H
# define PHLIO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_rule
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
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
}	t_philo;

//check.c
int		check_argv(int ac, char **av);

//util.c
int		ft_atoll(const char *str, int *num);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
