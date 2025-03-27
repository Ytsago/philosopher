/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:24:48 by secros            #+#    #+#             */
/*   Updated: 2025/03/26 11:43:46 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

# include <unistd.h>
# include <pthread.h>

/**
 * @brief All information related to one philo
 * @param r_fork Philosopher's fork
 * @param *l_fork Philosopher neighbourg's fork
 * @param time From last meal or start
 */
typedef struct s_philo	t_philo;

/**
 * @brief Contain data from user input
 * @param t_die Die if time until last meal is greater
 * @param t_sleep Time to sleep (after eating)
 * @param t_eat Time to eat
 * @param nb_philo Number of philosopher
 * @param nb_to_eat (OPTIONNAL) Number of time a philosopher has to eat
 */
typedef struct s_param	t_param;

/**
 * @brief Usefull mutex for writing and starting
 * @param printing If a philo need to write
 * @param start Before the simulation start
 */
typedef struct s_lock	t_lock;

/**
 * @brief Struct containg every information needed
 * @param param Struct t_param -> user input data
 * @param *philo Tab containing each philo
 * @param start Time when the simulation start
 * @param lock Usefull global mutex
 */
typedef struct s_data	t_data;

struct s_param
{
	unsigned int	t_die;
	unsigned int	t_sleep;
	unsigned int	t_eat;
	unsigned int	nb_philo;
	int				nb_to_eat;
};

struct s_lock
{
	pthread_mutex_t	printing;
	pthread_mutex_t	start;
};

struct s_philo
{
	time_t			time;
	unsigned int	philo;
	t_param			*param;
	t_lock			*lock;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
};

struct s_data
{
	t_param	param;
	t_philo	*philo;
	time_t	start;
	t_lock	lock;
};

#endif