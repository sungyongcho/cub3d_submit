/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 10:44:16 by sucho             #+#    #+#             */
/*   Updated: 2020/04/22 20:05:45 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ptr_dst;
	const char	*ptr_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	ptr_dst = dst;
	ptr_src = src;
	while (n--)
	{
		*ptr_dst++ = *ptr_src++;
	}
	return (dst);
}
