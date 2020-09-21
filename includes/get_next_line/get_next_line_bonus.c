/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 02:39:00 by sucho             #+#    #+#             */
/*   Updated: 2020/05/09 02:54:06 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char				*ft_clean_line(char *save, char **line, int r)
{
	unsigned int	i;
	char			*tmp;

	i = 0;
	while (*(save + i))
	{
		if (*(save + i) == '\n')
			break ;
		i++;
	}
	if (i < ft_strlen(save))
	{
		*line = ft_substr(save, 0, i);
		tmp = ft_substr(save, i + 1, ft_strlen(save));
		free(save);
		save = ft_strdup(tmp);
		free(tmp);
	}
	else if (r == 0)
	{
		*line = save;
		save = NULL;
	}
	return (save);
}

char				*ft_save_buffer(char *buffer, char *save)
{
	char			*store;

	if (save)
	{
		store = ft_strjoin(save, buffer);
		free(save);
		save = ft_strdup(store);
		free(store);
	}
	else
		save = ft_strdup(buffer);
	return (save);
}

int					get_next_line(int fd, char **line)
{
	static char		*storage[OPEN_MAX];
	char			buffer[BUFFER_SIZE + 1];
	int				result;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	while ((result = read(fd, buffer, BUFFER_SIZE)))
	{
		if (result == -1)
			return (-1);
		*(buffer + result) = '\0';
		storage[fd] = ft_save_buffer(buffer, storage[fd]);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (result <= 0 && !*(storage + fd))
	{
		*line = ft_strdup("");
		return (result);
	}
	storage[fd] = ft_clean_line(storage[fd], line, result);
	if (result <= 0 && !*(storage + fd))
		return (result);
	return (1);
}
