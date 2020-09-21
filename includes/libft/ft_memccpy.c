/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 14:09:14 by sucho             #+#    #+#             */
/*   Updated: 2020/04/22 20:07:36 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*ptr_d;
	unsigned const char	*ptr_s;

	if (dst == NULL && src == NULL)
		return (NULL);
	ptr_d = dst;
	ptr_s = src;
	while (n--)
	{
		if ((*ptr_d++ = *ptr_s++) == (unsigned char)c)
			return (ptr_d);
	}
	return (NULL);
}
