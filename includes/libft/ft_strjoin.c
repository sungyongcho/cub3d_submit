/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 21:53:03 by sucho             #+#    #+#             */
/*   Updated: 2020/09/05 17:03:39 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*result;

	if (s1 == 0 && s2 == 0)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(result = (char *)malloc(sizeof(char) * len)))
		return (0);
	ft_strlcpy(result, s1, len);
	ft_strlcat(result, s2, len);
	result[len - 1] = '\0';
	return (result);
}
