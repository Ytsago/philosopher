/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:29:48 by secros            #+#    #+#             */
/*   Updated: 2025/04/09 16:12:28 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_FUNCT_H
# define PHILO_FUNCT_H

//-------MAIN---------//
/**
 * @brief 
 * 
 * @param ac 
 * @param av nb_philo, t_die, t_eat, t_sleep, (nb_to_eat) 
 * @return int 
 */
int				main(int ac, char **av);

//-------UTILS-PARSING--------//
/**
 * @brief Check if a string contain only digit
 * 
 * @param str 
 * @return [1 : true] [0 : false]
 */
int				all_digit(char *str);
/**
 * @brief Basic atoi that detect overflow (only support positive)
 * 
 * @param str 
 * @param error is set to 1 in case of error
 * @return unsigned int 
 */
unsigned int	quick_atoi(char *str, char *error);
//-------UTILS-ROUTINE--------//

int				is_a_philo_dead(t_philo *philo);
int				is_dead(t_philo *philo);
void			philo_died(t_philo *philo);
long long		get_delta(struct timeval start);
int				micro_sleep(t_philo *philo, size_t time_param);
void			*wait_return(void);

//-------INIT---------//
/**
 * @brief Assign AV to each param using ui_atoi
 * 
 * @param param t_param struct
 * @param av User input
 * @return int --> Error is set to 1 in case of overflow or negative
 */
int				assign_param(t_param *param, char **av);
int				philo_init(t_data *data);
int				alloc_init(t_data *data);

//-------ROUTINE---------//

int				start(t_data *data);
void			*routine(void *args);
void			monitoring(t_data *data);

//-------FORK---------//

int				check_fork(t_philo *philo);
void			fork_unlock(t_philo *philo);

//-------ACTION---------//

int				sleeping(t_philo *philo);
int				try_to_eat(t_philo *philo);
void			printing(t_philo *philo, char action);

//-------THREAD---------//
/**
 * @brief Create each thread
 * 
 * @param data Struct --see philo_struct
 * @param th pthread_t pointer to create the threads
 * @return int [0 if success] [nb_of_thread if one fail]
 */
int				launch_thread(t_data *data, pthread_t *th);

/**
 * @brief Join each thread, if nb_th = 0 take the information from data->param
 * 
 * @param data Struct --see philo_struct
 * @param th pthread_t pointer (one per thread)
 * @param nb_th number of thread to join
 */
void			destroy_thread(t_data *data, pthread_t *th, size_t nb_th);

/**
 * @brief 
 * 
 */
int				new_mutex(pthread_mutex_t *new);

#endif