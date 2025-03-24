/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:29:48 by secros            #+#    #+#             */
/*   Updated: 2025/03/24 15:11:20 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_FUNCT_H
# define PHILO_FUNCT_H

//-------Utils---------//
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

#endif