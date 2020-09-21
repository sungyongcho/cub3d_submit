/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 00:42:17 by sucho             #+#    #+#             */
/*   Updated: 2020/07/13 15:40:00 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa(int n)
{
	long		value;
	size_t		count;
	char		*result;

	value = n;
	if ((count = 1) && value < 0)
		count++;
	if (value < 0)
		value *= -1;
	while ((value /= 10) > 0)
		count++;
	if (!(result = (char *)malloc(sizeof(char) * (count + 1))))
		return (NULL);
	value = (long)n * 10;
	if (value < 0)
	{
		result[0] = '-';
		value *= -1;
	}
	result[count--] = '\0';
	if (value == 0)
		result[count] = '0';
	while ((value /= 10) > 0)
		result[count--] = value % 10 + '0';
	return (result);
}
