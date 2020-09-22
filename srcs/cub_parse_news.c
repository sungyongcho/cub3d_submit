/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_news.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 09:18:42 by sucho             #+#    #+#             */
/*   Updated: 2020/09/22 18:39:43 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	setup_no_path(t_cub *cub, char *path)
{
	if (ft_strlen(cub->no_path) > 0)
		print_error_and_exit("Invalid .cub file; 'NO' already given\n");
	cub->no_path = ft_strdup(path);
}

void	setup_ea_path(t_cub *cub, char *path)
{
	if (ft_strlen(cub->ea_path) > 0)
		print_error_and_exit("Invalid .cub file; 'EA' already given\n");
	cub->ea_path = ft_strdup(path);
}

void	setup_we_path(t_cub *cub, char *path)
{
	if (ft_strlen(cub->we_path) > 0)
		print_error_and_exit("Invalid .cub file; 'WE' already given\n");
	cub->we_path = ft_strdup(path);
}

void	setup_so_path(t_cub *cub, char *path)
{
	if (ft_strlen(cub->so_path) > 0)
		print_error_and_exit("Invalid .cub file; 'SO' already given\n");
	cub->so_path = ft_strdup(path);
}

void	cub_parse_news(t_cub *cub, char **temp)
{
	if (!ft_strchr("NEWSFCR", (char)temp[0][0]))
		print_error_and_exit("Invalid .cub file; Check Resolution\n");
	check_valid_file(temp[1]);
	if ((char)temp[0][0] == 'N' && (char)temp[0][1] == 'O')
		setup_no_path(cub, temp[1]);
	else if ((char)temp[0][0] == 'E' && (char)temp[0][1] == 'A')
		setup_ea_path(cub, temp[1]);
	else if ((char)temp[0][0] == 'W' && (char)temp[0][1] == 'E')
		setup_we_path(cub, temp[1]);
	else if ((char)temp[0][0] == 'S' && (char)temp[0][1] == 'O')
		setup_so_path(cub, temp[1]);
	else
		print_error_and_exit("Invalid .cub file;  Check image path\n");
}
