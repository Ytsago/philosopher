/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:08:29 by secros            #+#    #+#             */
/*   Updated: 2025/03/30 18:08:55 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	sleeping(t_philo *philo)
{
	size_t	time;

	time = 0;
	pthread_mutex_lock(&philo->lock->printing);
	printf("%s%lld philo %d is sleeping\n%s", FG_BLUE, get_delta(philo->param->start), philo->philo, RESET);
	pthread_mutex_unlock(&philo->lock->printing);
	while (time < philo->param->t_sleep * 1000)
	{
		if (is_dead(philo) != 0)
			return (1);
		if (is_a_philo_dead(philo))
			return (1);
		usleep(100);
		time += 100;
	}
	return (0);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock->printing);
	printf("%s%lld philo %d is thinking\n%s", FG_GREEN, get_delta(philo->param->start), philo->philo, RESET);
	pthread_mutex_unlock(&philo->lock->printing);
}

int	try_to_eat(t_philo *philo)
{
	while (1)
	{
		if (is_a_philo_dead(philo) || is_dead(philo))
			return (1);
		if (check_fork(philo))
		{
			pthread_mutex_lock(&philo->lock->printing);
			printf("%s%lld philo %d is eating\n%s", FG_RED, get_delta(philo->param->start), philo->philo, RESET);
			pthread_mutex_unlock(&philo->lock->printing);
			if (gettimeofday(&philo->last_meal, NULL) != 0)
				return (2); //Not securized
			usleep(philo->param->t_eat * 1000);
			fork_unlock(philo);
			philo->eaten++;
			break ;
		}
		if (is_a_philo_dead(philo))
			return (1);
	}
	return (0);
}
