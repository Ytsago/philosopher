/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:09:13 by secros            #+#    #+#             */
/*   Updated: 2025/03/30 19:09:27 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	fork_unlock(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork.fork);
	pthread_mutex_lock(&philo->r_fork->fork);
	philo->l_fork.state = FREE;
	philo->r_fork->state = FREE;
	pthread_mutex_unlock(&philo->r_fork->fork);
	pthread_mutex_unlock(&philo->l_fork.fork);
}

int	check_fork(t_philo *philo)
{
	t_bool	eating;

	eating = 0;
	pthread_mutex_lock(&philo->l_fork.fork);
	if (philo->r_fork && philo->l_fork.state == FREE)
	{
		pthread_mutex_lock(&philo->r_fork->fork);
		if (philo->r_fork->state == FREE)
		{
			philo->l_fork.state = USED;
			philo->r_fork->state = USED;
			pthread_mutex_lock(&philo->lock->printing);
			printf("%s%lld philo %d has taken a fork\n%s", FG_YELLOW, \
				get_delta(philo->param->start), philo->philo, RESET);
			printf("%s%lld philo %d has taken a fork\n%s", FG_YELLOW, \
				get_delta(philo->param->start), philo->philo, RESET);
			pthread_mutex_unlock(&philo->lock->printing);
			eating = 1;
		}
		pthread_mutex_unlock(&philo->r_fork->fork);
	}
	pthread_mutex_unlock(&philo->l_fork.fork);
	return (eating);
}
