/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 18:37:51 by sucho             #+#    #+#             */
/*   Updated: 2020/09/21 03:40:31 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		move_player_arrow(t_window *window, int key_num)
{
	double	old_dir_x;
	double	old_plane_x;

	if (key_num == KEY_LEFT_ARROW)
	{
		old_dir_x = window->dirX;
		window->dirX = window->dirX * cos(window->rotSpeed)
						- window->dirY * sin(window->rotSpeed);
		window->dirY = old_dir_x * sin(window->rotSpeed) +
						 window->dirY * cos(window->rotSpeed);
		old_plane_x = window->planeX;
		window->planeX = window->planeX * cos(window->rotSpeed)
						- window->planeY * sin(window->rotSpeed);
		window->planeY = old_plane_x * sin(window->rotSpeed)
						+ window->planeY * cos(window->rotSpeed);
	}
	else if (key_num == KEY_RIGHT_ARROW)
	{
		old_dir_x = window->dirX;
		window->dirX = window->dirX * cos(-window->rotSpeed)
						- window->dirY * sin(-window->rotSpeed);
		window->dirY = old_dir_x * sin(-window->rotSpeed)
						+ window->dirY * cos(-window->rotSpeed);
		old_plane_x = window->planeX;
		window->planeX = window->planeX * cos(-window->rotSpeed)
						- window->planeY * sin(-window->rotSpeed);
		window->planeY = old_plane_x * sin(-window->rotSpeed)
						+ window->planeY * cos(-window->rotSpeed);
	}
}

void	move_player_w(t_window *window)
{
	int	fd_pos_x;
	int	fd_pos_y;

	fd_pos_x = (int)(window->posX + window->dirX * 2 * window->moveSpeed);
	fd_pos_y = (int)(window->posY + window->dirY * 2 * window->moveSpeed);
	if (window->cub->map[fd_pos_x][(int)(window->posY)] == '0')
		window->posX += window->dirX * window->moveSpeed;
	if (window->cub->map[(int)(window->posX)][fd_pos_y] == '0')
		window->posY += window->dirY * window->moveSpeed;
}

void	move_player_a(t_window *window)
{
	int	fd_pos_x;
	int	fd_pos_y;

	fd_pos_x = (int)(window->posX - window->dirX * 2 * window->moveSpeed);
	fd_pos_y = (int)(window->posY + window->dirY * 2 * window->moveSpeed);
	if (window->cub->map[fd_pos_x][(int)(window->posY)] == '0')
		window->posX -= window->dirY * window->moveSpeed;
	if (window->cub->map[(int)(window->posX)][fd_pos_y] == '0')
		window->posY += window->dirX * window->moveSpeed;
}

void	move_player_s(t_window *window)
{
	int	fd_pos_x;
	int	fd_pos_y;

	fd_pos_x = (int)(window->posX - window->dirX * (2 * window->moveSpeed));
	fd_pos_y = (int)(window->posY - window->dirY * (2 * window->moveSpeed));
	if (window->cub->map[fd_pos_x][(int)(window->posY)] == '0')
		window->posX -= window->dirX * window->moveSpeed;
	if (window->cub->map[(int)(window->posX)][fd_pos_y] == '0')
		window->posY -= window->dirY * window->moveSpeed;
}

void	move_player_d(t_window *window)
{
	int	fd_pos_x;
	int	fd_pos_y;

	fd_pos_x = (int)(window->posX + window->dirX * (2 * window->moveSpeed));
	fd_pos_y = (int)(window->posY - window->dirY * (2 * window->moveSpeed));
	if (window->cub->map[fd_pos_x][(int)(window->posY)] == '0')
		window->posX += window->dirY * window->moveSpeed;
	if (window->cub->map[(int)(window->posX)][fd_pos_y] == '0')
		window->posY -= window->dirX * window->moveSpeed;
}
