/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 15:27:36 by sucho             #+#    #+#             */
/*   Updated: 2020/09/21 19:10:56 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cub_parse_f_or_c(t_cub *cub, char **color, char which)
{
	int		i;
	int		j;

	if (which == 'F')
	{
		if (cub->floor_color)
			print_error_and_exit("Invalid .cub file; check if fields are given");
		i = 0;
		while (color[i])
		{
			if (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0)
				print_error_and_exit("Invalid .cub file; floor color out of range");
			j = 0;
			while(color[i][j])
			{
				if (!ft_isdigit(color[i][j++]))
					print_error_and_exit("Invalid .cub file; floor color out of range");
			}
			cub->floor_color = cub->floor_color * 256 + ft_atoi(color[i++]);
		}
	}
	if (which == 'C')
	{
		if (cub->ceiling_color)
			print_error_and_exit("Invalid .cub file; check if fields are given");
		i = 0;
		while (color[i])
		{
			if (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0)
				print_error_and_exit("Invalid .cub file; floor color out of range");
			j = 0;
			while(color[i][j])
			{
				if (!ft_isdigit(color[i][j++]))
					print_error_and_exit("Invalid .cub file; floor color out of range");
			}
			cub->ceiling_color = cub->ceiling_color * 256 + ft_atoi(color[i++]);
		}
	}
}

void	cub_parse_img(t_cub *cub, char **temp)
{
	if (!ft_strchr("NEWSFCR", (char)temp[0][0]))
		print_error_and_exit("Invalid .cub file; Check Resolution\n");
	check_valid_file(temp[1]);
	if ((char)temp[0][0] == 'N' && (char)temp[0][1] == 'O')
	{
		if (ft_strlen(cub->no_path) > 0)
			print_error_and_exit("Invalid .cub file; 'NO' already given\n");
		cub->no_path = ft_strdup(temp[1]);
	}
	else if ((char)temp[0][0] == 'E' && (char)temp[0][1] == 'A')
	{
		if (ft_strlen(cub->ea_path) > 0)
			print_error_and_exit("Invalid .cub file; 'EA' already given\n");
		cub->ea_path = ft_strdup(temp[1]);
	}
	else if ((char)temp[0][0] == 'W' && (char)temp[0][1] == 'E')
	{
		if (ft_strlen(cub->ea_path) > 0)
			print_error_and_exit("Invalid .cub file; Check 'WE' Path\n");
		cub->we_path = ft_strdup(temp[1]);
	}
	else if ((char)temp[0][0] == 'S' && (char)temp[0][1] == 'O')
	{
		if (ft_strlen(cub->ea_path) > 0)
			print_error_and_exit("Invalid .cub file; Check 'SO' Path\n");
		cub->so_path = ft_strdup(temp[1]);
	}
	else
		print_error_and_exit("Invalid .cub file;  Check image path\n");
}

void	cub_parse_res(t_cub *cub, char **temp, int split_count, int first_char)
{
	int	i;

	i = 0;
	if (split_count != 3)
		print_error_and_exit("Invalid .cub file; Check Resolution\n");
	else if (first_char == 'r')
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

void	cub_parse_rest(t_cub *cub, char **temp, int split_count)
{
	char**	color_temp;
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
		cub_parse_f_or_c(cub, color_temp, (char) temp[0][0]); // CHECK memory leah for color_temp
		free_2d_char(color_temp);
	}
	else
		print_error_and_exit("Invalid .cub file; Check .cub file is valid (hard)");
}

void	cub_parse_top_eight(t_cub *cub, char **cub_temp)
{
	int i;
	int	split_count;

	i = 0;
	char **temp;
	while (i < 8)
	{
		temp = ft_split(cub_temp[i], ' ');
		split_count = 0;
		while (temp[split_count])
			split_count++;
		if (2 > split_count || split_count > 3 || ft_isalpha(temp[0][0]) == 0 ||
			(split_count == 3 && (char)temp[0][0] != 'R'))
			print_error_and_exit("Invalid .cub file; check if all fields are given");
		if (ft_strlen(temp[0]) == 2)
			cub_parse_img(cub, temp);
		else
			cub_parse_rest(cub, temp, split_count);
		free_2d_char(temp);
		i++;
	}
}
