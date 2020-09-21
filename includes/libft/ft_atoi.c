/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:56:00 by sucho             #+#    #+#             */
/*   Updated: 2020/04/06 00:36:09 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t		sign;
	int			result;

	sign = 1;
	result = 0;
	while ((9 <= *nptr && *nptr <= 13) || (*nptr == 32))
	{
		nptr++;
	}
	while (*nptr == '-' || *nptr == '+')
	{
		if (result >= 1)
			return (0);
		if (*nptr == '-')
			sign = -1;
		result++;
		nptr++;
	}
	result = 0;
	while ('0' <= *nptr && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * result);
}
