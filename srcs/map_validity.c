/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 21:10:31 by sucho             #+#    #+#             */
/*   Updated: 2020/09/22 18:39:41 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			set_top_bot_space(t_window *window, char **max_pad)
{
	int			j;

	j = 0;
	while (j < window->cub->m_c + 2)
	{
		max_pad[0][j] = ' ';
		max_pad[window->cub->m_r + 1][j] = ' ';
		j++;
	}
	max_pad[0][j] = '\0';
	max_pad[window->cub->m_r + 1][j] = '\0';
}

void			fill_rest(t_window *window, char **max_pad)
{
	int			i;
	int			j;

	i = 0;
	while ((i + 1) < (window->cub->m_r + 1))
	{
		j = 0;
		max_pad[(i + 1)][j] = ' ';
		while ((j + 1) < (window->cub->m_c + 3))
		{
			if (j < (int)ft_strlen(window->cub->map[i]))
				max_pad[(i + 1)][(j + 1)] = window->cub->map[i][j];
			else
				max_pad[(i + 1)][(j + 1)] = ' ';
			j++;
		}
		max_pad[(i + 1)][j] = '\0';
		i++;
	}
}

char			**create_padded_square(t_window *window)
{
	char		**max_pad;
	int			i;

	if (!(max_pad =
		(char **)malloc(sizeof(char *) * (window->cub->m_r + 2))))
		return (0);
	i = -1;
	while (++i < window->cub->m_r + 2)
	{
		if (!(max_pad[i] =
			(char *)malloc(sizeof(char) * (window->cub->m_c + 3))))
			return (0);
	}
	set_top_bot_space(window, max_pad);
	fill_rest(window, max_pad);
	return (max_pad);
}

int				is_valid_map(t_window *window, int x, int y, int *visited)
{
	int			i;
	int			dx[4];
	int			dy[4];
	t_pos		to;

	if (x <= 0 || x >= window->cub->m_r + 1
		|| y <= 0 || y >= window->cub->m_c + 2)
		return (0);
	visited[y * (window->cub->m_r + 2) + x] = 1;
	init_vector_arrow(dx, dy);
	if (window->max_pad[x][y] == ' ')
		return (0);
	i = -1;
	while (++i < 4)
	{
		init_vector(&to, x + dx[i], y + dy[i]);
		if (0 <= to.x && to.x < window->cub->m_r + 2 && 0 <= to.y &&
		to.y < window->cub->m_c + 3 && window->max_pad[to.x][to.y] != '1' &&
		!visited[to.y * (window->cub->m_r + 2) + to.x])
		{
			if (!is_valid_map(window, to.x, to.y, visited))
				return (0);
		}
	}
	return (1);
}

void			check_map_valid(t_window *window, double pos_x, double pos_y)
{
	int			player_x;
	int			player_y;
	int			i;
	int			*visited;

	if (!(visited =
		(int *)malloc(sizeof(int) * ((window->cub->m_r + 2)
									* (window->cub->m_c + 3)))))
		return ;
	i = 0;
	while (i < (window->cub->m_r + 2) * (window->cub->m_c + 3))
		visited[i++] = 0;
	if (!(window->max_pad = create_padded_square(window)))
		return ;
	player_x = (int)(pos_x);
	player_y = (int)(pos_y);
	if (is_valid_map(window, player_x, player_y, visited) == 0)
		print_error_and_exit("Invalid .cub file; Not a valid map");
	free(visited);
	i = 0;
	while (i < window->cub->m_r + 2)
		free(window->max_pad[i++]);
	free(window->max_pad);
}
