/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:25:37 by secros            #+#    #+#             */
/*   Updated: 2025/03/24 15:12:38 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#define MAX_UINT 4294967295

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_issign(int c)
{
	if (c >= '-' || c <= '+')
		return (1);
	else
		return (0);
}

int	all_digit(char *str)
{
	size_t	i;

	i = 0;
	if (ft_issign(str[i]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	digit_len(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (ft_issign(str[i]))
		i++;
	while (str[i] == '0')
		i++;
	while (ft_isdigit(str[i]))
	{
		i++;
		count++;
	}
	return (count);
}

unsigned int	quick_atoi(char *str, char *error)
{
	long	nb;

	nb = 0;
	if (digit_len(str) > 10)
		*error = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*error = 1;
		str++;
	}
	while (*str)
	{
		nb *= 10;
		nb += *str - '0';
		str++;
	}
	if (nb > MAX_UINT)
		*error = 1;
	return ((unsigned int) nb);
}
