/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:09:13 by secros            #+#    #+#             */
/*   Updated: 2025/05/12 11:10:49 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	fork_unlock(t_fork *fork)
{
	pthread_mutex_lock(&fork->fork);
	fork->state = FREE;
	pthread_mutex_unlock(&fork->fork);
}

int	check_one(t_fork *fork)
{
	if (!fork)
		return (0);
	pthread_mutex_lock(&fork->fork);
	if (fork->state == FREE)
	{
		fork->state = USED;
		pthread_mutex_unlock(&fork->fork);
		return (1);
	}
	pthread_mutex_unlock(&fork->fork);
	return (0);
}

int	check_fork(t_philo *philo)
{
	t_fork	*fork[2];

	fork[philo->philo % 2 == 0] = &philo->l_fork;
	fork[philo->philo % 2 != 0] = philo->r_fork;
	while (!check_one(fork[1]))
	{
		if (is_a_philo_dead(philo))
			return (1);
		usleep(500);
	}
	printing(philo, FORK);
	while (!check_one(fork[0]))
	{
		if (is_a_philo_dead(philo))
		{
			fork_unlock(&philo->l_fork);
			return (1);
		}
		usleep(500);
	}
	printing(philo, FORK);
	return (0);
}
