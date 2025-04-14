/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:30:56 by secros            #+#    #+#             */
/*   Updated: 2025/04/14 18:36:53 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_bool	has_eaten_enough(t_philo *philo)
{
	int	nb_meal;

	if (philo->param->nb_to_eat == -1)
		return (0);
	pthread_mutex_lock(&philo->update);
	nb_meal = philo->eaten;
	pthread_mutex_unlock(&philo->update);
	if (nb_meal >= philo->param->nb_to_eat)
		return (1);
	return (0);
}

void	monitoring(t_data *data)
{
	size_t	nb;
	size_t	count;

	while (!is_a_philo_dead(data->philo))
	{
		nb = 0;
		count = 0;
		while (nb < data->param.nb_philo)
		{
			if (is_dead(&data->philo[nb]))
				return ;
			if (has_eaten_enough(&data->philo[nb]))
				count++;
			nb++;
		}
		if (count == data->param.nb_philo)
		{
			pthread_mutex_lock(&data->lock.is_alive);
			data->param.dead = 1;
			pthread_mutex_unlock(&data->lock.is_alive);
			return ;
		}
		usleep(1000);
	}
}
