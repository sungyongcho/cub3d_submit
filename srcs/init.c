/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:54:22 by sucho             #+#    #+#             */
/*   Updated: 2020/09/24 12:35:31 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		load_image(t_window *window, int i, char *path, t_img *img)
{
	int		x;
	int		y;

	img->img =
		mlx_xpm_file_to_image(window->mlx, path, &img->width, &img->height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
		&img->size_l, &img->endian);
	window->texture_size[i].x = img->width;
	window->texture_size[i].y = img->height;
	if (!(window->texture[i] =
		(int *)malloc(sizeof(int) * (img->width * img->height))))
		print_error_and_exit("Malloc error");
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			window->texture[i][img->width * y + x] =
				img->data[img->width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(window->mlx, img->img);
}

void		load_texture(t_window *window)
{
	t_img	temp;
	int		i;

	if (!(window->texture =
		(int **)malloc(sizeof(int*) * (TEXTURE_KIND))))
		print_error_and_exit("Malloc error");
	if (!(window->texture_size =
		(t_pos *)malloc(sizeof(t_pos) * (TEXTURE_KIND))))
		print_error_and_exit("Malloc error");
	i = 0;
	load_image(window, i++, window->cub->no_path, &temp);
	load_image(window, i++, window->cub->so_path, &temp);
	load_image(window, i++, window->cub->we_path, &temp);
	load_image(window, i++, window->cub->ea_path, &temp);
	load_image(window, i, window->cub->sprite_path, &temp);
}

void		init_window(t_window *window, char *path)
{
	int		i;
	int		mx_width;
	int		mx_height;

	window->mlx = mlx_init();
	if (!(window->cub = (t_cub *)malloc(sizeof(t_cub))))
		print_error_and_exit("Malloc error");
	cub_read_file(window, path);
	get_screen_res(&mx_width, &mx_height);
	window->cub->res_w = (window->cub->res_w < mx_width)
		? window->cub->res_w : mx_width;
	window->cub->res_h = (window->cub->res_h < mx_height)
		? window->cub->res_h : mx_height;
	window->win = mlx_new_window(window->mlx,
							window->cub->res_w, window->cub->res_h, "cub3D");
	if (!(window->buffer = (int **)malloc(sizeof(int *) * window->cub->res_h)))
		print_error_and_exit("Malloc error");
	i = -1;
	while (++i < window->cub->res_h)
	{
		if (!(window->buffer[i] =
			(int *)malloc(sizeof(int) * window->cub->res_w + 1)))
			print_error_and_exit("Malloc error");
	}
	load_texture(window);
}

void		init_temp(t_window *window)
{
	window->move_speed = 0.05;
	window->rot_speed = 0.05;
	window->img.img =
		mlx_new_image(window->mlx, window->cub->res_w, window->cub->res_h);
	window->img.data =
		(int *)mlx_get_data_addr(window->img.img, &window->img.bpp,
		&window->img.size_l, &window->img.endian);
}

void		init_sprite(t_window *window)
{
	if (!(window->z_buffer =
			(double *)malloc(sizeof(double) * (window->cub->res_w))))
		print_error_and_exit("Malloc error");
	if (!(window->sprite_order =
			(int *)malloc(sizeof(int) * (window->cub->sprite_count))))
		print_error_and_exit("Malloc error");
	if (!(window->sprite_dist =
			(double *)malloc(sizeof(double) * (window->cub->sprite_count))))
		print_error_and_exit("Malloc error");
}
