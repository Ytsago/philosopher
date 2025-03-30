/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:24:48 by secros            #+#    #+#             */
/*   Updated: 2025/03/30 12:38:17 by secros           ###   ########.fr       */
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

/**
 * @brief Struct containing a mutex and boolean to represent the fork state
 * @param fork a mutex for the current fork
 * @param state a boolean for the fork state
 */
typedef struct s_fork	t_fork;

typedef char			t_bool;

enum e_state
{
	FREE,
	USED,
};

struct s_fork
{
	pthread_mutex_t	fork;
	t_bool			state;
};

struct s_param
{
	unsigned int	t_die;
	unsigned int	t_sleep;
	unsigned int	t_eat;
	unsigned int	nb_philo;
	int				nb_to_eat;
	t_bool			dead;
};

struct s_lock
{
	pthread_mutex_t	printing;
	pthread_mutex_t	start;
};

struct s_philo
{
	time_t			last_meal;
	unsigned int	philo;
	t_fork			l_fork;
	t_param			*param;
	t_lock			*lock;
	t_fork			*r_fork;
	int				eaten;
};

struct s_data
{
	t_param		param;
	t_philo		*philo;
	time_t		start;
	t_lock		lock;
};

#endif