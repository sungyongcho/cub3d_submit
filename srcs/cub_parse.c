/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 15:27:36 by sucho             #+#    #+#             */
/*   Updated: 2020/09/22 18:39:44 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		free_2d_char(char **ptr)
{
	int		i;

	i = 0;
	while (*(ptr + i))
		free(*(ptr + i++));
	free(ptr);
}

char		*cub_read_line(const char *path)
{
	int		fd;
	char	*temp;
	char	*store;
	char	*line;

	if ((fd = open(path, O_RDONLY)) != 3)
	{
		perror(ft_strjoin("Error\n", path));
		exit(1);
	}
	store = ft_strdup("");
	while (get_next_line(fd, &line))
	{
		temp = ft_strjoin(store, line);
		free(store);
		store = temp;
		temp = ft_strjoin(store, "\n");
		free(store);
		store = temp;
		free(line);
	}
	free(line);
	close(fd);
	return (store);
}

void		init_cub(t_cub *cub)
{
	cub->res_w = 0;
	cub->res_h = 0;
	cub->floor_color = 0;
	cub->ceiling_color = 0;
	cub->m_r = 0;
	cub->m_c = 0;
	cub->sprite_count = 0;
	cub->no_path = "";
	cub->so_path = "";
	cub->ea_path = "";
	cub->we_path = "";
	cub->sprite_path = "";
	cub->player_check = 0;
}

void		cub_count_max_column(t_cub *cub)
{
	int		i;
	int		m_c;

	m_c = 0;
	i = 0;
	while (i < cub->m_r)
	{
		if (m_c < (int)ft_strlen(cub->map[i]))
		{
			m_c = (int)ft_strlen(cub->map[i]);
		}
		i++;
	}
	cub->m_c = m_c;
}

void		cub_read_file(t_window *window, const char *path)
{
	char	*cub_oneline;
	char	**cub_temp;
	int		m_r_count;

	init_cub(window->cub);
	cub_oneline = cub_read_line(path);
	cub_temp = ft_split(cub_oneline, '\n');
	m_r_count = 0;
	while (*(cub_temp + m_r_count))
		m_r_count++;
	m_r_count -= 8;
	window->cub->m_r = m_r_count;
	cub_parse_top_eight(window->cub, cub_temp);
	cub_parse_map(window->cub, (cub_temp + 8), m_r_count);
	cub_count_max_column(window->cub);
	cub_map_checkout(window);
	cub_save_sprite(window);
	check_map_valid(window, window->pos_x, window->pos_y);
	free(cub_oneline);
	free_2d_char(cub_temp);
	cub_temp = NULL;
}
