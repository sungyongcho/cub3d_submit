/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 18:32:45 by sucho             #+#    #+#             */
/*   Updated: 2020/09/23 06:16:41 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <math.h>
# include <float.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "./mlx_openGL/mlx.h"
# include <CoreGraphics/CGDisplayConfiguration.h>
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT_ARROW 123
# define KEY_RIGHT_ARROW 124
# define KEY_ESC 53
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_EXIT 17
# define TEXTURE_KIND 5

/*
**	for struct
*/

typedef struct	s_img
{
	void		*img;
	int			*data;

	int			size_l;
	int			bpp;
	int			endian;

	int			width;
	int			height;
}				t_img;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		distance;
}				t_sprite;

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_cub
{
	int			res_w;
	int			res_h;
	char		*no_path;
	char		*so_path;
	char		*ea_path;
	char		*we_path;
	char		*sprite_path;
	int			player_check;
	int			floor_color;
	int			ceiling_color;
	char		**map;
	int			m_r;
	int			m_c;
	int			sprite_count;
}				t_cub;

typedef struct	s_window
{
	void		*mlx;
	void		*win;
	t_cub		*cub;
	t_img		img;
	t_pos		*texture_size;
	t_sprite	*sprite;
	char		**max_pad;
	double		*z_buffer;
	int			*sprite_order;
	double		*sprite_dist;
	int			sprite_count;
	int			**texture;
	int			**buffer;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
}				t_window;

typedef struct	s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	int			step;
	int			tex_pos;
	int			step_x;
	int			step_y;
	int			side;
	int			line_h;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			tex_num;
	int			draw_s;
	int			draw_e;
}				t_ray;

typedef struct	s_ray_sprite
{
	double		sprite_x;
	double		sprite_y;
	double		inv_dir;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_h;
	int			sprite_w;
	int			draw_s_y;
	int			draw_e_y;
	int			draw_s_x;
	int			draw_e_x;
}				t_ray_sprite;

/*
**	main.c
*/

int				key_press(int key, t_window *window);
void			calc(t_window *window);
void			draw(t_window *window);

/*
**	init.c
*/

void			load_image(t_window *window, int i, char *path, t_img *img);
void			load_texture(t_window *window);
void			init_window(t_window *window, char *path);
void			init_temp(t_window *window);
void			init_sprite(t_window *window);

/*
**	init_vector.c
*/
void			init_vector(t_pos *to, int x, int y);

/*
**	Keyboard Input
*/

/*
**	key_wasd.c
*/

void			move_player_w(t_window *window);
void			move_player_a(t_window *window);
void			move_player_s(t_window *window);
void			move_player_d(t_window *window);

/*
**	key_lr.c
*/
void			update_left(t_window *window, double old_d_x, double old_p_x);
void			update_right(t_window *window, double old_d_x, double old_p_x);
void			move_player_arrow(t_window *window, int key);

/*
**	Map Parsing / Handling
*/

/*
**	cub_parse.c
*/
void			free_2d_char(char **ptr);
char			*cub_read_line(const char *path);
void			init_cub(t_cub *cub);
void			cub_count_max_column(t_cub *cub);
void			cub_read_file(t_window *window, const char *path);

/*
**	cub_parse_path.c
*/
void			cub_parse_f(t_cub *cub, char **color);
void			cub_parse_c(t_cub *cub, char **color);
void			cub_parse_res(t_cub *cub, char **temp, int split_count, int c);
void			cub_parse_rest(t_cub *cub, char **temp, int split_count);
void			cub_parse_top_eight(t_cub *cub, char **cub_temp);

/*
**	cub_parse_news.c
*/
void			setup_no_path(t_cub *cub, char *path);
void			setup_ea_path(t_cub *cub, char *path);
void			setup_we_path(t_cub *cub, char *path);
void			setup_so_path(t_cub *cub, char *path);
void			cub_parse_news(t_cub *cub, char **temp);

/*
**	cub_parse_map.c
*/
int				map_count_end_space(char *s);
void			cub_parse_map(t_cub *cub, char **line, int line_count);
void			map_pre_validity(t_window *window, int i, int j);
void			cub_map_checkout(t_window *window);
void			cub_save_sprite(t_window *window);

/*
**	cub_set_player.c
*/

void			cub_set_player_n(t_window *window);
void			cub_set_player_e(t_window *window);
void			cub_set_player_w(t_window *window);
void			cub_set_player_s(t_window *window);
void			cub_set_player(t_window *window, char pos, int i, int j);

/*
**	Drawing and Raycasting
*/

/*
**	raycast_wall.c
*/

void			set_step_and_side(t_window *window, t_ray *ray);
void			find_and_calc_wall(t_window *window, t_ray *ray);
void			calculate_wall_texture(t_window *window, t_ray *ray);
void			init_ray(int x, t_window *window, t_ray *ray);
void			wall_to_buffer(t_window *window, int x);

/*
**	raycast_rest.c
*/

void			floor_ceiling_to_buffer(t_window *window, int x);
void			sort_sprites(t_window *window);
void			init_ray_sprite(t_window *window, t_ray_sprite *rs, int i);
void			draw_spr_tex(t_window *window, t_ray_sprite *rs, int count);
void			draw_sprite(t_window *window, int i);

/*
**	bmp.c
*/
void			set_int_in_char(unsigned char *start, int value);
void			write_bmp_header(t_window *window, int fd, int size);
void			write_data(t_window *window, int fd);
int				save_bmp(t_window *window);
void			bmp_mode(t_window *window, char *path);

/*
**	map_validity.c
*/
void			set_top_bot_space(t_window *window, char **max_pad);
void			fill_rest(t_window *window, char **max_pad);
char			**create_padded_square(t_window *window);
int				is_valid_map(t_window *window, int x, int y, int *visited);
void			check_map_valid(t_window *window, double pos_x, double pos_y);

/*
**	error_process.c
*/

void			print_error_and_exit(char *msg);
void			check_valid_file(char *filepath);

/*
**	screen_util.c
*/

int				screen_exit(void);
void			get_screen_res(int *mx_x, int *mx_y);

#endif
