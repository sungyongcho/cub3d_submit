/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:09:16 by sucho             #+#    #+#             */
/*   Updated: 2020/04/25 18:51:40 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t n;
	size_t index_src;

	if (dst == NULL && src == NULL)
		return (0);
	index_src = ft_strlen(src);
	if (dstsize == 0)
		return (index_src + dstsize);
	n = 0;
	while (n < index_src && n < dstsize - 1)
	{
		dst[n] = src[n];
		n++;
	}
	if (dstsize > 0)
		dst[n] = 0;
	return (index_src);
}
