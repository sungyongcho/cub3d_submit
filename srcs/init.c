/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:54:22 by sucho             #+#    #+#             */
/*   Updated: 2020/09/22 04:33:15 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_image(t_window *window, int texture_index, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(window->mlx, path, &img->width, &img->height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	window->texture_size[texture_index].x = img->width;
	window->texture_size[texture_index].y = img->height;
	if (!(window->texture[texture_index] = (int *)malloc(sizeof(int) * (img->width * img->height))))
			return ;
	for (int y = 0; y < img->height; y++)
	{
		for (int x = 0; x < img->width; x++)
		{
			window->texture[texture_index][img->width * y + x] = img->data[img->width * y + x];
		}
	}
	mlx_destroy_image(window->mlx, img->img);
}

void	load_texture(t_window *window)
{
	t_img	temp;
	int		i;

	if (!(window->texture = (int **)malloc(sizeof(int*) * (TEXTURE_KIND))))
		return ;
	if (!(window->texture_size = (t_pos *)malloc(sizeof(t_pos) * (TEXTURE_KIND))))
		return ;
	i = 0;
	load_image(window, i++, window->cub->no_path, &temp);
	load_image(window, i++, window->cub->so_path, &temp);
	load_image(window, i++, window->cub->we_path, &temp);
	load_image(window, i++, window->cub->ea_path, &temp);
	load_image(window, i, window->cub->sprite_path, &temp);
}
void	init_window(t_window *window, char *path)
{
	int	i;

	window->mlx = mlx_init();
	if (!(window->cub = (t_cub *)malloc(sizeof(t_cub))))
		return ;
	cub_read_file(window, path);
	window->win = mlx_new_window(window->mlx,
							window->cub->res_w, window->cub->res_h, "cub3D");
	if (!(window->buffer = (int **)malloc(sizeof(int *) * window->cub->res_h)))
		return ;
	i = 0;
	while (i < window->cub->res_h)
	{
		if (!(window->buffer[i] = (int *)malloc(sizeof(int) * window->cub->res_w + 1)))
			return ;
		i++;
	}
	load_texture(window);
}

void	init_temp(t_window *window)
{
	window->moveSpeed = 0.05;
	window->rotSpeed = 0.05;
	window->img.img = mlx_new_image(window->mlx, window->cub->res_w, window->cub->res_h);
	window->img.data = (int *)mlx_get_data_addr(window->img.img, &window->img.bpp, &window->img.size_l, &window->img.endian);
}

void	init_sprite(t_window *window)
{
	if (!(window->z_buffer = (double *)malloc(sizeof(double) * (window->cub->res_w))))
		return ;
	if (!(window->spriteOrder = (int *)malloc(sizeof(int) * (window->cub->sprite_count))))
		return ;
	if (!(window->spriteDistance = (double *)malloc(sizeof(double) * (window->cub->sprite_count))))
		return ;
}
