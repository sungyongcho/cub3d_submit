/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_wasd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 18:37:51 by sucho             #+#    #+#             */
/*   Updated: 2020/09/22 18:14:32 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_player_w(t_window *window)
{
	int	fd_pos_x;
	int	fd_pos_y;

	fd_pos_x = (int)(window->pos_x +
				(window->dir_x * (2 * window->move_speed)));
	fd_pos_y = (int)(window->pos_y +
				(window->dir_y * (2 * window->move_speed)));
	if (window->cub->map[fd_pos_x][(int)(window->pos_y)] == '0')
		window->pos_x += window->dir_x * window->move_speed;
	if (window->cub->map[(int)(window->pos_x)][fd_pos_y] == '0')
		window->pos_y += window->dir_y * window->move_speed;
}

void	move_player_a(t_window *window)
{
	int	fd_pos_x;
	int	fd_pos_y;

	fd_pos_x = (int)(window->pos_x
				- (window->dir_y * (2 * window->move_speed)));
	fd_pos_y = (int)(window->pos_y
				+ (window->dir_x * (2 * window->move_speed)));
	if (window->cub->map[fd_pos_x][(int)(window->pos_y)] == '0')
		window->pos_x += -(window->dir_y * window->move_speed);
	if (window->cub->map[(int)(window->pos_x)][fd_pos_y] == '0')
		window->pos_y += (window->dir_x * window->move_speed);
}

void	move_player_s(t_window *window)
{
	int	fd_pos_x;
	int	fd_pos_y;

	fd_pos_x = (int)(window->pos_x
				- (window->dir_x * (2 * window->move_speed)));
	fd_pos_y = (int)(window->pos_y
				- (window->dir_y * (2 * window->move_speed)));
	if (window->cub->map[fd_pos_x][(int)(window->pos_y)] == '0')
		window->pos_x -= window->dir_x * window->move_speed;
	if (window->cub->map[(int)(window->pos_x)][fd_pos_y] == '0')
		window->pos_y -= window->dir_y * window->move_speed;
}

void	move_player_d(t_window *window)
{
	int	fd_pos_x;
	int	fd_pos_y;

	fd_pos_x = (int)(window->pos_x
				+ (window->dir_y * (2 * window->move_speed)));
	fd_pos_y = (int)(window->pos_y
				- (window->dir_x * (2 * window->move_speed)));
	if (window->cub->map[fd_pos_x][fd_pos_y] == '0')
		window->pos_x += (window->dir_y * window->move_speed);
	if (window->cub->map[(int)(window->pos_x)][fd_pos_y] == '0')
		window->pos_y += -(window->dir_x * window->move_speed);
}
