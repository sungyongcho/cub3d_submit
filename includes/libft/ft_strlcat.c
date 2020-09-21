/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 03:00:21 by sucho             #+#    #+#             */
/*   Updated: 2020/04/22 17:57:15 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	result;
	size_t	index_dest;
	size_t	index_src;

	index_dest = ft_strlen(dst);
	index_src = ft_strlen(src);
	if (index_dest >= dstsize || dstsize == 0)
		return (index_src + dstsize);
	if (dstsize < index_dest)
		result = dstsize + index_src;
	else
		result = index_dest + index_src;
	index_src = 0;
	while (index_dest < dstsize - 1 && src[index_src] != '\0')
		dst[index_dest++] = src[index_src++];
	dst[index_dest] = '\0';
	return (result);
}
