/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:06:08 by secros            #+#    #+#             */
/*   Updated: 2025/04/27 16:15:26 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	get_delta(struct timeval start)
{
	long long			delta;
	struct timeval		d_start;
	struct timeval		actual;

	if (gettimeofday(&actual, NULL) != 0)
		return (-1);
	d_start.tv_sec = actual.tv_sec - start.tv_sec;
	d_start.tv_usec = actual.tv_usec - start.tv_usec;
	if (d_start.tv_usec < 0)
	{
		d_start.tv_sec -= 1;
		d_start.tv_usec += 1000000;
	}
	delta = d_start.tv_sec * 1000 + d_start.tv_usec / 1000;
	return (delta);
}

void	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock->is_alive);
	philo->param->dead = 1;
	pthread_mutex_unlock(&philo->lock->is_alive);
	pthread_mutex_lock(&philo->lock->printing);
	printf("%s%lld philo %d died\n%s", FG_MAGENTA, \
		get_delta(philo->param->start), philo->philo, RESET);
	pthread_mutex_unlock(&philo->lock->printing);
}

int	is_dead(t_philo *philo)
{
	long long	delta;

	pthread_mutex_lock(&philo->update);
	delta = get_delta(philo->last_meal);
	pthread_mutex_unlock(&philo->update);
	if (delta >= philo->param->t_die)
	{
		philo_died(philo);
		return (1);
	}
	return (0);
}

int	is_a_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock->is_alive);
	if (philo->param->dead)
	{
		pthread_mutex_unlock(&philo->lock->is_alive);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock->is_alive);
	return (0);
}
