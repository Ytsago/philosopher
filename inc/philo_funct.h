/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:29:48 by secros            #+#    #+#             */
/*   Updated: 2025/03/27 12:54:09 by secros           ###   ########.fr       */
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

//-------UTILS---------//
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

//-------INIT---------//
/**
 * @brief Assign AV to each param using ui_atoi
 * 
 * @param param t_param struct
 * @param av User input
 * @return int --> Error is set to 1 in case of overflow or negative
 */
int				assign_param(t_param *param, char **av);
void			philo_init(t_data *data);
int				alloc_init(t_data *data);

//-------ROUTINE---------//
int	start(t_data *data);
void	*routine(void *args);

#endif