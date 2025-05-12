/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:29:48 by secros            #+#    #+#             */
/*   Updated: 2025/05/12 13:45:05 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_FUNCT_H
# define PHILO_FUNCT_H

//-------MAIN---------//

/**
 * @brief 
 * 
 * @param ac 
 * @param av [nb_philo], [t_die], [t_eat], [t_sleep], ([nb_to_eat]) 
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

/**
 * @brief Check if a philo is dead 
 * 
 * @param philo 
 * @return [1] if a philo is dead
 * 
 * [0] if all philo are alive
 */
int				is_a_philo_dead(t_philo *philo);

/**
 * @brief Check if a philo as exceed time_to_die
 * 
 * if yes call philo_died to update and print
 * 
 * @param philo The philo to be evaluated
 * @return [0] is alive
 * 
 * [1] The philo is dead
 */
int				is_dead(t_philo *philo);

/**
 * @brief Update the param->dead to 1 to signify that a philo is dead
 * 
 * Print that the philo has died
 * 
 * @param philo The dead philosophe
 */
void			philo_died(t_philo *philo);

/**
 * @brief Get the delta time (T2 - T1)
 * 
 * @param start A timeval struct that contain a previous timestamp
 * @return long long 
 */
long long		get_delta(struct timeval start);

//-------INIT---------//

/**
 * @brief Assign AV to each param using ui_atoi
 * 
 * @param param t_param struct
 * @param av User input
 * @return [error] set to 1 in case of overflow or negative
 */
int				assign_param(t_param *param, char **av);

/**
 * @brief Initialise the basic pointer and information of each philosophe
 * 
 * also init their mutexes so the function can fail
 * 
 * @param data a struct that contain a pointer to a philo tab
 * @return [0] on success
 * 
 * [1] on failure (mutex)
 */
int				philo_init(t_data *data);

/**
 * @brief Allocated the philosopher tab and init the basics mutexes needed
 * 
 * @param data A struct containing philo and lock
 * @return [0] on success 
 * 
 *  [1] on failure
 * 
 */
int				alloc_init(t_data *data);

//-------ROUTINE---------//

/**
 * @brief One of the core function of this project,
 * 
 * Call different function to allocated philosophe and mutexes
 * 
 * Create all the thread and if one fail destroy them (also if tine fail)
 * 
 * Init some basic information like start_time
 * 
 * Unlock the philo to start the simulation and call the monitoring
 * 
 * @param data Struct containing all information
 * @return [0] on success
 * 
 * [1] on failure
 */
int				start(t_data *data);

/**
 * @brief All the step that a philo has to follow
 * 
 * The start is lock by a mutex
 * 
 * Philos will : Think, Try to eat (and eat), sleep
 * 
 * End when the monitoring set the dead varaible to 1
 * @param args A philosophe
 * @return NULL
 */
void			*routine(void *args);

/**
 * @brief Check constantly if a philo is_dead and set the dead variable to 1
 * 
 * Also check if all the philo has eaten nb_of_time to end the simulation
 * 
 * @param data Struct t_data
 */
void			monitoring(t_data *data);

//-------FORK---------//

/**
 * @brief Check if both forks are availbe
 * 
 * @param philo The philo that want to take the forks
 * @return [1] philo is ready to eat
 * 
 * [0] one or both fork are unvaiable
 */
int				check_fork(t_philo *philo);

/**
 * @brief Release one fork and make it usable
 * 
 * @param fork The fork to release
 */
void			fork_unlock(t_fork *fork);

//-------ACTION---------//

int				sleeping(t_philo *philo);

/**
 * @brief A while (1) where the philo will try to take both fork if possible
 * 
 * it will start to eat after a succes
 * 
 * It will also stop if a philo died before it could take the fork
 * 
 * @param philo The philo that want to take the fork
 * @return [0] if success
 * 
 *  [1 - 2] if a philo died or gettimeofday fail
 */
int				try_to_eat(t_philo *philo);

/**
 * @brief Use to print a message on the terminal
 * 
 * Use of mutex to prevent datarace
 * 
 * @param philo The philo that want to print
 * @param action The message to print
 */
void			printing(t_philo *philo, char action);

/**
 * @brief Print thinking and if there is an odd number of philo, wait time to eat
 * 
 * @param philo 
 * @return int, [0] Success, [1] Error,
 */
int				thinking(t_philo *philo);

//-------THREAD---------//
/**
 * @brief Create each thread
 * 
 * @param data Struct --see philo_struct
 * @param th pthread_t pointer to create the threads
 * @return [0] if success
 * 
 *  [nb_of_thread] if one fail
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
 * @brief Initialise a new mutex and add it to the garbage collection
 * 
 * @param new The adress of the mutex to init
 * @return [0] = SUCCESS 
 * 
 * [1] = ERROR
 */
int				new_mutex(pthread_mutex_t *new);

/**
 * @brief Check if a philo has enough time to do his action without dying
 * 
 * @param philo 
 * @param action 
 * @return int 
 */
int				smart_sleep(t_philo *philo, int action);

#endif