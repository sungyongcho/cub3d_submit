/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:21:08 by sucho             #+#    #+#             */
/*   Updated: 2020/09/22 03:45:40 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray(int x, t_window *window, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)window->cub->res_w - 1;
	ray->ray_dir_x = window->dirX + window->planeX * ray->camera_x;
	ray->ray_dir_y = window->dirY + window->planeY * ray->camera_x;
	ray->map_x = (int)window->posX;
	ray->map_y = (int)window->posY;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	set_step_and_side(t_window *window, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (window->posX - ray->map_x) \
							* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - window->posX) \
							* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (window->posY - ray->map_y) \
							* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - window->posY) \
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
	if (ray->side == 0)
		ray->perp_wall_dist = ((ray->map_x - window->posX) + (1 - ray->step_x) / 2) \
							/ ray->ray_dir_x;
	else
		ray->perp_wall_dist = ((ray->map_y - window->posY) + (1 - ray->step_y) / 2) \
							/ ray->ray_dir_y;
}

void	calculate_wall_texture(t_window *window, t_ray *ray)
{
	ray->line_height = (int)(window->cub->res_h / ray->perp_wall_dist);

	if ((ray->draw_start = -ray->line_height / 2 + window->cub->res_h / 2) < 0)
		ray->draw_start = 0;
	if ((ray->draw_end = ray->line_height / 2 + window->cub->res_h /2 ) >= window->cub->res_h)
		ray->draw_end = window->cub->res_h - 1;

	if (ray->side == 0)
	{
		ray->tex_num = (ray->ray_dir_x > 0) ? 1 : 0;
		ray->wall_x = window->posY + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		ray->tex_num = (ray->ray_dir_y < 0) ? 3 : 2;
		ray->wall_x = window->posX + ray->perp_wall_dist * ray->ray_dir_x;
	}
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)window->texture_size[ray->tex_num].x);
	if ((ray->side == 0 && ray->ray_dir_x > 0) \
	 	|| (ray->side == 1 && ray->ray_dir_y < 0))
		ray->tex_x = window->texture_size[ray->tex_num].x - ray->tex_x - 1;
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
	set_step_and_side(window, ray);
	find_and_calc_wall(window, ray);
	calculate_wall_texture(window,ray);
	step = window->texture_size[ray->tex_num].y * 1.0 / ray->line_height;
	tex_pos = (ray->draw_start - window->cub->res_h / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while(y< ray->draw_end)
	{
		ray->tex_y = (int)tex_pos & (window->texture_size[ray->tex_num].y - 1);
		tex_pos += step;
		color = window->texture[ray->tex_num][
			window->texture_size[ray->tex_num].y * ray->tex_y +ray->tex_x];
		if(ray->side == 1)
			color = (color >> 1) & 8355711;
		window->buffer[y][x] = color;
		y++;
	}
	window->z_buffer[x] = ray->perp_wall_dist;
	free(ray);
}
