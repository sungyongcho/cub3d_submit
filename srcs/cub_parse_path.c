/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 15:27:36 by sucho             #+#    #+#             */
/*   Updated: 2020/09/22 18:39:44 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		cub_parse_f(t_cub *cub, char **color)
{
	int		i;
	int		j;

	if (cub->floor_color)
		print_error_and_exit("Invalid .cub file; check if fields are given");
	i = 0;
	while (color[i])
	{
		if (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0)
			print_error_and_exit("Invalid .cub file; check fllor color");
		j = 0;
		while (color[i][j])
		{
			if (!ft_isdigit(color[i][j++]))
				print_error_and_exit("Invalid .cub file; check floor color");
		}
		cub->floor_color = cub->floor_color * 256 + ft_atoi(color[i++]);
	}
}

void		cub_parse_c(t_cub *cub, char **color)
{
	int		i;
	int		j;

	if (cub->ceiling_color)
		print_error_and_exit("Invalid .cub file; check if fields are given");
	i = 0;
	while (color[i])
	{
		if (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0)
			print_error_and_exit("Invalid .cub file; check ceiling color");
		j = 0;
		while (color[i][j])
		{
			if (!ft_isdigit(color[i][j++]))
				print_error_and_exit("Invalid .cub file; check ceiling color");
		}
		cub->ceiling_color = cub->ceiling_color * 256 + ft_atoi(color[i++]);
	}
}

void		cub_parse_res(t_cub *cub, char **temp, int split_count, int c)
{
	int		i;

	i = 0;
	if (split_count != 3)
		print_error_and_exit("Invalid .cub file; Check Resolution\n");
	else if (c == 'r')
		print_error_and_exit("Invalid .cub file; Check Resolution\n");
	else if (cub->res_w != 0 || cub->res_h != 0)
		print_error_and_exit("Invalid .cub file; Check Resolution\n");
	i = 0;
	while (temp[1][i])
	{
		if (!ft_isdigit(temp[1][i++]))
			print_error_and_exit("Invalid .cub file; Check Resolution\n");
	}
	i = 0;
	while (temp[2][i])
	{
		if (!ft_isdigit(temp[2][i++]))
			print_error_and_exit("Invalid .cub file; Check Resolution\n");
	}
	cub->res_w = ft_atoi(temp[1]);
	cub->res_h = ft_atoi(temp[2]);
}

void		cub_parse_rest(t_cub *cub, char **temp, int split_count)
{
	char	**color_temp;
	int		j;

	j = 0;
	if ((char)temp[0][0] == 'R' || (char)temp[0][0] == 'r')
		cub_parse_res(cub, temp, split_count, (int)temp[0][0]);
	else if ((char)temp[0][0] == 'S')
	{
		if (ft_strlen(cub->sprite_path))
			print_error_and_exit("Invalid .cub file; Sprite already given");
		check_valid_file(temp[1]);
		cub->sprite_path = ft_strdup(temp[1]);
	}
	else if ((char)temp[0][0] == 'F' || (char)temp[0][0] == 'C')
	{
		color_temp = ft_split(temp[1], ',');
		if ((char)temp[0][0] == 'F')
			cub_parse_f(cub, color_temp);
		else
			cub_parse_c(cub, color_temp);
		free_2d_char(color_temp);
	}
	else
		print_error_and_exit("Invalid .cub file; Check .cub file is valid");
}

void		cub_parse_top_eight(t_cub *cub, char **cub_temp)
{
	char	**temp;
	int		i;
	int		split_count;

	i = 0;
	while (i < 8)
	{
		temp = ft_split(cub_temp[i], ' ');
		split_count = 0;
		while (temp[split_count])
			split_count++;
		if (2 > split_count || split_count > 3 || ft_isalpha(temp[0][0]) == 0 ||
			(split_count == 3 && (char)temp[0][0] != 'R'))
			print_error_and_exit("Invalid .cub file; field missing");
		if (ft_strlen(temp[0]) == 2)
			cub_parse_news(cub, temp);
		else
			cub_parse_rest(cub, temp, split_count);
		free_2d_char(temp);
		i++;
	}
}
