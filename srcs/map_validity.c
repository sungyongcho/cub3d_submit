/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 21:10:31 by sucho             #+#    #+#             */
/*   Updated: 2020/09/21 19:1 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
static void		set_top_bot_space(t_window *window, char **max_pad)
{
	int			j;

	j = 0;
	while (j < window->cub->max_col + 2)
	{
		max_pad[0][j] = ' ';
		max_pad[window->cub->map_row + 1][j] = ' ';
		j++;
	}
	max_pad[0][j] = '\0';
	max_pad[window->cub->map_row + 1][j] = '\0';
}
static void		fill_rest(t_window *window, char **max_pad)
{
	int	i;
	int	j;

	i = 0;
	while ((i + 1) < (window->cub->map_row + 1))
	{
		j = 0;
		max_pad[(i+1)][j] = ' ';
		while ((j +1) < (window->cub->max_col + 3))
		{
			if (j < (int) ft_strlen(window->cub->map[i]))
				max_pad[(i + 1)][(j + 1)] = window->cub->map[i][j];
			else
				max_pad[(i + 1)][(j + 1)] = ' ';
			j++;
		}
		max_pad[(i + 1)][j] ='\0';
		i++;
	}
}
char	**create_padded_square(t_window *window)
{
	char	**max_pad;
	int i;

	if (!(max_pad = (char **)malloc(sizeof(char *) * (window->cub->map_row + 2))))
		return (0);
	i = 0;
	while (i < window->cub->map_row + 2)
	{
		if(!(max_pad[i] = (char *)malloc(sizeof(char) * (window->cub->max_col + 3))))
			return (0);
		i++;
	}
	set_top_bot_space(window, max_pad);
	fill_rest(window, max_pad);
	return (max_pad);
}
void	init_vector(t_pos *to, int x, int y)
{
	to->x = x;
	to->y = y;
}
int		is_valid_map(t_window *window, char **max_pad, int x, int y, int *visited)
{
	int		i;
	int		*dx;
	int		*dy;
	t_pos	to;

	if (x <= 0 || x >= window->cub->map_row + 1 || y <= 0 || y >= window->cub->max_col + 2)
		return (0);
	visited[y * (window->cub->map_row + 2) + x] = 1;
	dx = (int[4]){1, -1, 0, 0};
	dy = (int[4]){0, 0, -1, 1};
	i = 0;
	if (max_pad[x][y] == ' ')
		return (0);
	while (i < 4)
	{
		init_vector(&to, x + dx[i], y + dy[i]);
		if (0 <= to.x && to.x < window->cub->map_row + 2 &&
			0 <= to.y && to.y < window->cub->max_col + 3 &&
			max_pad[to.x][to.y] != '1' &&
			!visited[to.y * (window->cub->map_row + 2) + to.x])
		{
			if(!is_valid_map(window, max_pad, to.x, to.y, visited))
				return (0);
		}
		i++;
	}
	return (1);
}
void	check_map_validity(t_window *window, double posX, double posY)
{
	char **max_pad;
	int	player_x;
	int	player_y;
	int	i;
	int	*visited;

	if (!(visited = (int *)malloc(sizeof(int) * ((window->cub->map_row + 2) * (window->cub->max_col + 3)))))
		return ;
	i = 0;
	while (i < (window->cub->map_row + 2) * (window->cub->max_col + 3))
		visited[i++] = 0;
	if (!(max_pad = create_padded_square(window)))
		return ;
	player_x = (int)(posX);
	player_y = (int)(posY);
	if (is_valid_map(window, max_pad, player_x, player_y, visited) == 0)
		print_error_and_exit("Invalid .cub file; Not a valid map");
	free(visited);
	i = 0;
	while(i < window->cub->map_row + 2)
		free(max_pad[i++]);
	free(max_pad);
}

