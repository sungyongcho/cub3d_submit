/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:16:58 by sucho             #+#    #+#             */
/*   Updated: 2020/09/16 16:24:02 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

void	write_bmp_header(t_window *window, int fd, int size)
{
	unsigned char	header[54];

	ft_memset(header, 0, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	set_int_in_char(header + 2, size);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	set_int_in_char(header + 18, window->cub->res_w);
	set_int_in_char(header + 22, window->cub->res_h);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	write(fd, header, 54);
}

void	write_data(t_window *window, int fd)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					pad;

	i = window->cub->res_h-1;
	pad = (4 - (window->cub->res_w * 3) % 4) % 4;
	while (i >= 0)
	{
		j = 0;
		while (j < window->cub->res_w)
		{
			write(fd, &(window->buffer[i][j]), 3);
			if (pad > 0)
				write(fd, &zero, pad);
			j++;
		}
		i--;
	}
}

int		save_bmp(t_window *window)
{
	int	fd;
	int	size;

	size = 54 + 3 * window->cub->res_w * window->cub->res_h;
	if ((fd = open("./screenshot.bmp", O_WRONLY | O_CREAT |\
						O_TRUNC | O_APPEND, 00755)) < 0)
		return (0);
	write_bmp_header(window, fd, size);
	write_data(window, fd);
	return (1);
}
