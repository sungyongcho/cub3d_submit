/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_lr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 18:37:51 by sucho             #+#    #+#             */
/*   Updated: 2020/09/22 18:39:39 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		update_left(t_window *window, double old_d_x, double old_p_x)
{
	window->dir_x = window->dir_x * cos(window->rot_speed)
					- window->dir_y * sin(window->rot_speed);
	window->dir_y = old_d_x * sin(window->rot_speed) +
						window->dir_y * cos(window->rot_speed);
	window->plane_x = window->plane_x * cos(window->rot_speed)
					- window->plane_y * sin(window->rot_speed);
	window->plane_y = old_p_x * sin(window->rot_speed)
					+ window->plane_y * cos(window->rot_speed);
}

void		update_right(t_window *window, double old_d_x, double old_p_x)
{
	window->dir_x = window->dir_x * cos(-window->rot_speed)
					- window->dir_y * sin(-window->rot_speed);
	window->dir_y = old_d_x * sin(-window->rot_speed)
					+ window->dir_y * cos(-window->rot_speed);
	window->plane_x = window->plane_x * cos(-window->rot_speed)
					- window->plane_y * sin(-window->rot_speed);
	window->plane_y = old_p_x * sin(-window->rot_speed)
					+ window->plane_y * cos(-window->rot_speed);
}

void		move_player_arrow(t_window *window, int key_num)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = window->dir_x;
	old_plane_x = window->plane_x;
	if (key_num == KEY_LEFT_ARROW)
		update_left(window, old_dir_x, old_plane_x);
	else if (key_num == KEY_RIGHT_ARROW)
		update_right(window, old_dir_x, old_plane_x);
}
