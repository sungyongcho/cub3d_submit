/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 05:50:12 by sucho             #+#    #+#             */
/*   Updated: 2020/09/21 19:06:10 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_error_and_exit(char *msg)
{
	int	message_length;

	message_length = ft_strlen(msg);
	write(1, "Error\n", 6);
	write(1, &*msg, message_length);
	exit(1);
}

void	check_valid_file(char *filepath)
{
	int	fd;

	if ((fd  = open(filepath,O_RDONLY)) != 3)
	{
		perror(ft_strjoin("Error\n",filepath));
		exit(0);
	}
	close(fd);
}
