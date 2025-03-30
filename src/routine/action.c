/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:08:29 by secros            #+#    #+#             */
/*   Updated: 2025/03/30 18:48:38 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	sleeping(t_philo *philo)
{
	size_t	time;

	time = 0;
	pthread_mutex_lock(&philo->lock->printing);
	printf("%s%lld philo %d is sleeping\n%s", FG_BLUE, \
		get_delta(philo->param->start), philo->philo, RESET);
	pthread_mutex_unlock(&philo->lock->printing);
	return (micro_sleep(philo, philo->param->t_sleep));
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock->printing);
	printf("%s%lld philo %d is thinking\n%s", FG_GREEN, \
		get_delta(philo->param->start), philo->philo, RESET);
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
			printf("%s%lld philo %d is eating\n%s", FG_RED, \
				get_delta(philo->param->start), philo->philo, RESET);
			pthread_mutex_unlock(&philo->lock->printing);
			if (gettimeofday(&philo->last_meal, NULL) != 0)
				return (2); //Not securized
			if (micro_sleep(philo, philo->param->t_eat) != 0)
				return (1);
			fork_unlock(philo);
			philo->eaten++;
			break ;
		}
	}
	return (0);
}
