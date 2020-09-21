/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 20:08:41 by sucho             #+#    #+#             */
/*   Updated: 2020/04/22 14:57:15 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	index;

	index = 0;
	while (*s)
	{
		s++;
		index++;
	}
	while (index >= 0)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
		index--;
	}
	return (NULL);
}
