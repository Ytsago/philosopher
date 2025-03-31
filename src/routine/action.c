/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:08:29 by secros            #+#    #+#             */
/*   Updated: 2025/03/31 01:51:31 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	sleeping(t_philo *philo)
{
	if (is_a_philo_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->lock->printing);
	printf("%s%lld philo %d is sleeping\n%s", FG_BLUE, \
		get_delta(philo->param->start), philo->philo, RESET);
	pthread_mutex_unlock(&philo->lock->printing);
	usleep(philo->param->t_sleep * 1000);
	return (0);
}

void	thinking(t_philo *philo)
{
	if (is_a_philo_dead(philo))
		return ;
	pthread_mutex_lock(&philo->lock->printing);
	printf("%s%lld philo %d is thinking\n%s", FG_GREEN, \
		get_delta(philo->param->start), philo->philo, RESET);
	pthread_mutex_unlock(&philo->lock->printing);
}

int	try_to_eat(t_philo *philo)
{
	while (1)
	{
		if (is_a_philo_dead(philo))
			return (1);
		if (check_fork(philo))
		{
			pthread_mutex_lock(&philo->lock->printing);
			printf("%s%lld philo %d is eating\n%s", FG_RED, \
				get_delta(philo->param->start), philo->philo, RESET);
			pthread_mutex_unlock(&philo->lock->printing);
			pthread_mutex_lock(&philo->update);
			if (gettimeofday(&philo->last_meal, NULL) != 0)
				return (2); //Not securized
			philo->eaten++;
			pthread_mutex_unlock(&philo->update);
			usleep(philo->param->t_eat * 1000);
			fork_unlock(philo);
			if (sleeping(philo))
				return (1);
			break ;
		}
		usleep(300);
	}
	return (0);
}
