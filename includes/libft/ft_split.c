/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 03:06:16 by sucho             #+#    #+#             */
/*   Updated: 2020/04/27 18:58:59 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_word_count(char const *s, char c)
{
	size_t		count;
	bool		is_word;

	count = 0;
	is_word = false;
	while (*s)
	{
		if (is_word == false && *s != c)
		{
			count++;
			is_word = true;
		}
		else if (is_word == true && *s == c)
			is_word = false;
		s++;
	}
	return (count);
}

static size_t	pos_word(char *s, char c, size_t order)
{
	bool		is_word;
	size_t		count;
	size_t		position;

	is_word = false;
	count = 0;
	position = 0;
	while (*(s + position))
	{
		if (is_word == false && *(s + position) != c)
		{
			count++;
			if (count == order + 1)
				break ;
			is_word = true;
		}
		else if (is_word == true && *(s + position) == c)
			is_word = false;
		position++;
	}
	return (position);
}

static char		*assign_word(char *s, char c)
{
	size_t		i;
	size_t		len;
	char		*result;

	len = 0;
	while (*(s + len) && *(s + len) != c)
		len++;
	if (!(result = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (i < len)
		*(result + (i++)) = *s++;
	*(result + i) = '\0';
	return (result);
}

char			**ft_split(char const *s, char c)
{
	size_t		w_count;
	size_t		i;
	char		**result;
	char		*temp;

	if (!s)
		return (NULL);
	temp = (char *)s;
	w_count = get_word_count(temp, c);
	if (!(result = (char **)malloc(sizeof(char *) * (w_count + 1))))
		return (0);
	i = 0;
	while (i < w_count)
	{
		*(result + i) = assign_word(temp + pos_word(temp, c, i), c);
		i++;
	}
	*(result + i) = 0;
	return (result);
}
