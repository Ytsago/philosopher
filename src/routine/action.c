/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:08:29 by secros            #+#    #+#             */
/*   Updated: 2025/04/14 09:45:55 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	sleeping(t_philo *philo)
{
	if (is_a_philo_dead(philo))
		return (1);
	printing(philo, SLEEP);
	usleep(philo->param->t_sleep * 1000);
	return (0);
}

void	printing(t_philo *philo, char action)
{
	pthread_mutex_lock(&philo->lock->printing);
	if (is_a_philo_dead(philo))
	{
		pthread_mutex_unlock(&philo->lock->printing);
		return ;
	}
	if (action == THINK)
		printf("%s%lld philo %d is thinking\n%s", FG_GREEN, \
			get_delta(philo->param->start), philo->philo, RESET);
	if (action == FORK)
	{
		printf("%s%lld philo %d has taken a fork\n%s", FG_YELLOW, \
			get_delta(philo->param->start), philo->philo, RESET);
		printf("%s%lld philo %d has taken a fork\n%s", FG_YELLOW, \
			get_delta(philo->param->start), philo->philo, RESET);
	}
	if (action == EAT)
		printf("%s%lld philo %d is eating\n%s", FG_RED, \
			get_delta(philo->param->start), philo->philo, RESET);
	if (action == SLEEP)
		printf("%s%lld philo %d is sleeping\n%s", FG_BLUE, \
			get_delta(philo->param->start), philo->philo, RESET);
	pthread_mutex_unlock(&philo->lock->printing);
}

int	try_to_eat(t_philo *philo)
{
	while (1)
	{
		if (is_a_philo_dead(philo))
			return (1);
		if (check_fork(philo) == 3)
		{
			printing(philo, EAT);
			pthread_mutex_lock(&philo->update);
			if (gettimeofday(&philo->last_meal, NULL) != 0)
			{
				pthread_mutex_unlock(&philo->update);
				return (2);
			}
			philo->eaten++;
			pthread_mutex_unlock(&philo->update);
			usleep(philo->param->t_eat * 1000);
			fork_unlock(&philo->l_fork);
			fork_unlock(philo->r_fork);
			break ;
		}
		usleep(300);
	}
	return (0);
}
