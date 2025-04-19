/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:32:32 by secros            #+#    #+#             */
/*   Updated: 2025/04/19 14:54:40 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	assign_param(t_param *param, char **av)
{
	char	error;

	error = 0;
	param->nb_philo = quick_atoi(av[1], &error);
	if (param->nb_philo > MAX_PHILO)
		return (1);
	param->t_die = quick_atoi(av[2], &error);
	param->t_eat = quick_atoi(av[3], &error);
	param->t_sleep = quick_atoi(av[4], &error);
	if (av[5])
		param->nb_to_eat = quick_atoi(av[5], &error);
	else
		param->nb_to_eat = -1;
	param->dead = 0;
	return (error);
}

int	philo_init(t_data *data)
{
	size_t	nb;
	size_t	i;

	nb = data->param.nb_philo;
	i = 0;
	while (i < nb)
	{
		data->philo[i].lock = &data->lock;
		data->philo[i].param = &data->param;
		if (nb == 1)
			data->philo[i].r_fork = NULL;
		else
			data->philo[i].r_fork = &data->philo[(i + 1) % nb].l_fork;
		data->philo[i].eaten = 0;
		data->philo[i].l_fork.state = FREE;
		if (new_mutex(&data->philo[i].l_fork.fork))
			return (1);
		if (new_mutex(&data->philo[i].update))
			return (1);
		i++;
	}
	return (0);
}

int	alloc_init(t_data *data)
{
	data->philo = malloc((sizeof(t_philo) * data->param.nb_philo));
	if (!data->philo)
		return (1);
	if (new_mutex(&data->lock.start))
		return (1);
	if (new_mutex(&data->lock.printing))
		return (1);
	if (new_mutex(&data->lock.is_alive))
		return (1);
	return (0);
}
