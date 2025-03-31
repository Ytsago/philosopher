/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:22:55 by secros            #+#    #+#             */
/*   Updated: 2025/03/31 01:31:41 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*wait_return(void)
{
	usleep(1000);
	return (NULL);
}

int	new_mutex(pthread_mutex_t *new)
{
	if (pthread_mutex_init(new, NULL) != 0)
		return (1);
	if (!fill_dishwasher(new, (void (*)(void *)) \
	pthread_mutex_destroy, get_sink(NULL)))
	{
		pthread_mutex_destroy(new);
		return (1);
	}
	return (0);
}

int	launch_thread(t_data *data, pthread_t *th)
{
	size_t	nb;

	nb = 0;
	while (nb < data->param.nb_philo)
	{
		data->philo[nb].philo = nb + 1;
		if (pthread_create(&th[nb], NULL, &routine, &data->philo[nb]) != 0)
			return (nb + 1);
		nb++;
	}
	return (0);
}

void	destroy_thread(t_data *data, pthread_t *th, size_t nb_th)
{
	size_t	nb;

	nb = 0;
	if (nb_th == 0)
		nb_th = data->param.nb_philo;
	else
		nb_th--;
	while (nb < nb_th)
	{
		pthread_join(th[nb], NULL);
		nb++;
	}
	do_dishes(get_sink(NULL));
}
