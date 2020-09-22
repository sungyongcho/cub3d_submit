/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:21:08 by sucho             #+#    #+#             */
/*   Updated: 2020/09/22 18:39:42 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_step_and_side(t_window *window, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (window->pos_x - ray->map_x) \
							* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - window->pos_x) \
							* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (window->pos_y - ray->map_y) \
							* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - window->pos_y) \
							* ray->delta_dist_y;
	}
}

void	find_and_calc_wall(t_window *window, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (window->cub->map[ray->map_x][ray->map_y] == '1')
			hit = 1;
	}
	ray->perp_wall_dist = (ray->side == 0) ?
			((ray->map_x - window->pos_x)
			+ (1 - ray->step_x) / 2) / ray->ray_dir_x :
			((ray->map_y - window->pos_y)
			+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void	calculate_wall_texture(t_window *window, t_ray *ray)
{
	ray->line_h = (int)(window->cub->res_h / ray->perp_wall_dist);
	if ((ray->draw_s = -ray->line_h / 2 + window->cub->res_h / 2) < 0)
		ray->draw_s = 0;
	if ((ray->draw_e = ray->line_h / 2 + window->cub->res_h / 2)
		>= window->cub->res_h)
		ray->draw_e = window->cub->res_h - 1;
	if (ray->side == 0)
	{
		ray->tex_num = (ray->ray_dir_x > 0) ? 1 : 0;
		ray->wall_x = window->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		ray->tex_num = (ray->ray_dir_y < 0) ? 3 : 2;
		ray->wall_x = window->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	}
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x =
		(int)(ray->wall_x * (double)window->texture_size[ray->tex_num].x);
	if ((ray->side == 0 && ray->ray_dir_x > 0) \
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		ray->tex_x = window->texture_size[ray->tex_num].x - ray->tex_x - 1;
}

void	init_ray(int x, t_window *window, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)window->cub->res_w - 1;
	ray->ray_dir_x = window->dir_x + window->plane_x * ray->camera_x;
	ray->ray_dir_y = window->dir_y + window->plane_y * ray->camera_x;
	ray->map_x = (int)window->pos_x;
	ray->map_y = (int)window->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	set_step_and_side(window, ray);
	find_and_calc_wall(window, ray);
	calculate_wall_texture(window, ray);
}

void	wall_to_buffer(t_window *window, int x)
{
	t_ray	*ray;
	double	step;
	double	tex_pos;
	int		color;
	int		y;

	if (!(ray = (t_ray *)malloc(sizeof(t_ray))))
		return ;
	init_ray(x, window, ray);
	step = window->texture_size[ray->tex_num].y * 1.0 / ray->line_h;
	tex_pos = (ray->draw_s - window->cub->res_h / 2 + ray->line_h / 2) * step;
	y = ray->draw_s;
	while (y < ray->draw_e)
	{
		ray->tex_y = (int)tex_pos & (window->texture_size[ray->tex_num].y - 1);
		tex_pos += step;
		color = window->texture[ray->tex_num][
			window->texture_size[ray->tex_num].y * ray->tex_y + ray->tex_x];
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		window->buffer[y][x] = color;
		y++;
	}
	window->z_buffer[x] = ray->perp_wall_dist;
	free(ray);
}
