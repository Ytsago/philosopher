/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:09:13 by secros            #+#    #+#             */
/*   Updated: 2025/04/25 08:51:09 by secros           ###   ########.fr       */
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
	char	eating;

	eating = check_one(&philo->l_fork);
	eating += check_one(philo->r_fork) * 2;
	if (eating == 0)
		return (0);
	else if (eating == 1)
		fork_unlock(&philo->l_fork);
	else if (eating == 2)
		fork_unlock(philo->r_fork);
	else
		printing(philo, FORK);
	return (eating);
}
