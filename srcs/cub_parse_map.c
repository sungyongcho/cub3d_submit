/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 15:27:36 by sucho             #+#    #+#             */
/*   Updated: 2020/09/24 12:31:03 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		map_count_end_space(char *s)
{
	int	i;
	int	output;

	i = ft_strlen(s) - 1;
	output = 0;
	while (i != 0)
	{
		if (ft_strchr("NEWS012", s[i]))
			return (output);
		output++;
		i--;
	}
	return (output);
}

void	cub_parse_map(t_cub *cub, char **line, int line_count)
{
	int	i;
	int	space_cnt;

	if (!(cub->map = (char **)malloc(sizeof(char *) * line_count)))
		print_error_and_exit("Malloc error");
	i = 0;
	while (line[i])
	{
		space_cnt = (int)ft_strlen(line[i]) - map_count_end_space(line[i]) + 1;
		if (!(cub->map[i] = (char *)malloc(sizeof(char) * (space_cnt + 1))))
			print_error_and_exit("Malloc error");
		ft_strlcpy(cub->map[i], line[i], space_cnt);
		i++;
	}
}

void	map_pre_validity(t_window *window, int i, int j)
{
	if (!(ft_strchr("NEWS 012", (char)window->cub->map[i][j])))
		print_error_and_exit("Invalid .cub file; contains invalid char.");
	else if (ft_strchr("NEWS", (char)window->cub->map[i][j]))
	{
		if (window->cub->player_check == 1)
			print_error_and_exit("Invalid .cub file; check player pos.");
		window->cub->player_check = 1;
		cub_set_player(window, (char)window->cub->map[i][j], i, j);
		window->cub->map[i][j] = '0';
	}
	if (window->cub->map[i][j] == '2')
		window->cub->sprite_count++;
}

void	cub_map_checkout(t_window *window)
{
	int		i;
	int		j;

	i = 0;
	while (i < window->cub->m_r)
	{
		j = 0;
		while (window->cub->map[i][j])
		{
			map_pre_validity(window, i, j);
			j++;
		}
		i++;
	}
	if (!window->cub->player_check)
		print_error_and_exit("Invalid .cub file; player pos. n/a");
}

void	cub_save_sprite(t_window *window)
{
	int		i;
	int		j;
	int		sprite_count;

	if (!(window->sprite =
		(t_sprite *)malloc(sizeof(t_sprite) * window->cub->sprite_count)))
		print_error_and_exit("Malloc error");
	sprite_count = 0;
	i = 0;
	while (i < window->cub->m_r)
	{
		j = 0;
		while (window->cub->map[i][j])
		{
			if (window->cub->map[i][j] == '2')
			{
				window->sprite[sprite_count].x = i;
				window->sprite[sprite_count].y = j;
				window->cub->map[i][j] = '0';
				sprite_count++;
			}
			j++;
		}
		i++;
	}
}
