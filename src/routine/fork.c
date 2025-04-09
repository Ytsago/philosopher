/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:09:13 by secros            #+#    #+#             */
/*   Updated: 2025/04/09 16:11:26 by secros           ###   ########.fr       */
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
			printing(philo, FORK);
			eating = 1;
		}
		pthread_mutex_unlock(&philo->r_fork->fork);
	}
	pthread_mutex_unlock(&philo->l_fork.fork);
	return (eating);
}
