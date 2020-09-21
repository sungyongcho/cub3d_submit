/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 14:16:27 by sucho             #+#    #+#             */
/*   Updated: 2020/04/22 20:08:11 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	char		*d_last;
	const char	*s;
	const char	*s_last;

	d = dst;
	s = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (d < s)
	{
		while (len--)
			*d++ = *s++;
	}
	else
	{
		s_last = s + (len - 1);
		d_last = d + (len - 1);
		while (len--)
			*d_last-- = *s_last--;
	}
	return (dst);
}
