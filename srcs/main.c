/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 09:50:32 by sucho             #+#    #+#             */
/*   Updated: 2020/09/24 12:04:51 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			draw(t_window *window)
{
	int			x;
	int			y;

	y = 0;
	while (y < window->cub->res_h)
	{
		x = 0;
		while (x < window->cub->res_w)
		{
			window->img.data[y * window->cub->res_w + x] = window->buffer[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(window->mlx, window->win, window->img.img, 0, 0);
}

void			calc(t_window *window)
{
	int			x;
	int			i;

	x = 0;
	while (x < window->cub->res_w)
		floor_ceiling_to_buffer(window, x++);
	x = 0;
	while (x < window->cub->res_w)
		wall_to_buffer(window, x++);
	i = 0;
	while (i < window->cub->sprite_count)
	{
		window->sprite[i].distance =
			((window->pos_x - window->sprite[i].x) \
			* (window->pos_x - window->sprite[i].x) \
			+ (window->pos_y - window->sprite[i].y) \
			* (window->pos_y - window->sprite[i].y));
		i++;
	}
	sort_sprites(window);
	i = 0;
	while (i < window->cub->sprite_count)
		draw_sprite(window, i++);
}

int				main_loop(t_window *window)
{
	calc(window);
	draw(window);
	return (0);
}

int				key_press(int key, t_window *window)
{
	if (key == KEY_W)
		move_player_w(window);
	else if (key == KEY_A)
		move_player_a(window);
	else if (key == KEY_S)
		move_player_s(window);
	else if (key == KEY_D)
		move_player_d(window);
	else if (key == KEY_LEFT_ARROW || key == KEY_RIGHT_ARROW)
		move_player_arrow(window, key);
	else if (key == KEY_ESC)
	{
		free(window);
		exit(0);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_window	*window;

	if (!(window = (t_window *)malloc(sizeof(t_window))))
		print_error_and_exit("Malloc error");
	if (argc == 2)
	{
		init_window(window, argv[1]);
		init_temp(window);
		init_sprite(window);
		mlx_loop_hook(window->mlx, main_loop, window);
		mlx_hook(window->win, X_EVENT_KEY_PRESS, 1, key_press, window);
		mlx_hook(window->win, X_EVENT_KEY_EXIT, 1L << 5, screen_exit, window);
		mlx_loop(window->mlx);
	}
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 6) == 0)
		bmp_mode(window, argv[1]);
	else
		print_error_and_exit("A .cub file path not given");
	return (0);
}
