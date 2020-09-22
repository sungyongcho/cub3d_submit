/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_set_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 05:19:20 by sucho             #+#    #+#             */
/*   Updated: 2020/09/22 18:39:42 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cub_set_player_n(t_window *window)
{
	window->dir_x = -1;
	window->dir_y = 0;
	window->plane_x = 0;
	window->plane_y = 0.66;
}

void	cub_set_player_e(t_window *window)
{
	window->dir_x = 0;
	window->dir_y = -1;
	window->plane_x = -0.66;
	window->plane_y = 0;
}

void	cub_set_player_w(t_window *window)
{
	window->dir_x = 0;
	window->dir_y = 1;
	window->plane_x = 0.66;
	window->plane_y = 0;
}

void	cub_set_player_s(t_window *window)
{
	window->dir_x = 1;
	window->dir_y = 0;
	window->plane_x = 0;
	window->plane_y = -0.66;
}

void	cub_set_player(t_window *window, char pos, int i, int j)
{
	window->pos_x = i + 0.5;
	window->pos_y = j + 0.5;
	if (pos == 'N')
		cub_set_player_n(window);
	if (pos == 'E')
		cub_set_player_e(window);
	if (pos == 'W')
		cub_set_player_w(window);
	if (pos == 'S')
		cub_set_player_s(window);
}
