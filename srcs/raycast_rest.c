/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_rest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:21:08 by sucho             #+#    #+#             */
/*   Updated: 2020/09/24 12:05:51 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void				floor_ceiling_to_buffer(t_window *window, int x)
{
	int				y;

	y = 0;
	while (y < window->cub->res_h / 2)
	{
		window->buffer[y][x] = window->cub->ceiling_color;
		y++;
	}
	y = window->cub->res_h / 2;
	while (y < window->cub->res_h)
	{
		window->buffer[y][x] = window->cub->floor_color;
		y++;
	}
}

void				sort_sprites(t_window *window)
{
	int				i;
	int				j;
	int				max;
	t_sprite		temp;

	i = 0;
	max = 0;
	while (i < window->cub->sprite_count - 1)
	{
		max = i;
		j = i + 1;
		while (j < window->cub->sprite_count)
		{
			if (window->sprite[j].distance > window->sprite[i].distance)
				max = j;
			j++;
		}
		if (i != max)
		{
			temp = window->sprite[i];
			window->sprite[i] = window->sprite[max];
			window->sprite[max] = temp;
		}
		i++;
	}
}

void				init_ray_sprite(t_window *window, t_ray_sprite *rs, int i)
{
	rs->sprite_x = window->sprite[i].x - window->pos_x;
	rs->sprite_y = window->sprite[i].y - window->pos_y;
	rs->inv_dir = 1.0 / ((window->plane_x * window->dir_y)
						- (window->dir_x * window->plane_y));
	rs->transform_x = rs->inv_dir * ((window->dir_y * rs->sprite_x)
									- (window->dir_x * rs->sprite_y));
	rs->transform_y = rs->inv_dir * ((-window->plane_y * rs->sprite_x)
									+ (window->plane_x * rs->sprite_y));
	rs->sprite_screen_x = (int)((window->cub->res_w / 2)
								* (1 + rs->transform_x / rs->transform_y));
	rs->sprite_h = abs((int)(window->cub->res_h / (rs->transform_y)));
	rs->sprite_w = abs((int)(window->cub->res_h / (rs->transform_y)));
	rs->draw_s_y = -rs->sprite_h / 2 + window->cub->res_h / 2;
	if (rs->draw_s_y < 0)
		rs->draw_s_y = 0;
	rs->draw_e_y = rs->sprite_h / 2 + window->cub->res_h / 2;
	if (rs->draw_e_y >= window->cub->res_h)
		rs->draw_e_y = window->cub->res_h - 1;
	rs->draw_s_x = -rs->sprite_w / 2 + rs->sprite_screen_x;
	if (rs->draw_s_x < 0)
		rs->draw_s_x = 0;
	rs->draw_e_x = rs->sprite_w / 2 + rs->sprite_screen_x;
	if (rs->draw_e_x >= window->cub->res_w)
		rs->draw_e_x = window->cub->res_w - 1;
}

void				draw_spr_tex(t_window *window, t_ray_sprite *rs, int count)
{
	int				tex_x;
	int				tex_y;
	int				y;
	int				d;
	int				color;

	tex_x = (int)(256 *
			(count - (-rs->sprite_w / 2 + rs->sprite_screen_x))
			* window->texture_size[4].x / rs->sprite_w) / 256;
	if (rs->transform_y > 0
		&& count > 0
		&& count < window->cub->res_w
		&& rs->transform_y < window->z_buffer[count])
	{
		y = rs->draw_s_y;
		while (y < rs->draw_e_y)
		{
			d = (y) * 256 - window->cub->res_h * 128 + rs->sprite_h * 128;
			tex_y = ((d * 64) / rs->sprite_h) / 256;
			color = window->texture[4][64 * tex_y + tex_x];
			if ((color & 0x00FFFFFF) != 0)
				window->buffer[y][count] = color;
			y++;
		}
	}
}

void				draw_sprite(t_window *window, int i)
{
	t_ray_sprite	*rs;
	int				count;

	if (!(rs = (t_ray_sprite *)malloc(sizeof(t_ray_sprite))))
		print_error_and_exit("Malloc error");
	init_ray_sprite(window, rs, i);
	count = rs->draw_s_x;
	while (count < rs->draw_e_x)
	{
		draw_spr_tex(window, rs, count);
		count++;
	}
	free(rs);
}
