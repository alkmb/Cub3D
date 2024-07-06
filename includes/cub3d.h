/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:00:41 by akambou           #+#    #+#             */
/*   Updated: 2024/07/02 04:18:59 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
//-----------------------DEFINES------------------------------------------------
# define SUCCESS 0
# define FAILURE 1
# define TRUE 1
# define FALSE 0
# define FLOOR_COLOR 0xFF0000
# define CEILING_COLOR 0x00FF00
//-----------------------KEYS--------------------------------------------------
# define KEY_W 119
# define EVENT_CLOSE_BTN 17
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_M 109
# define KEY_P 112
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
//-----------------------MATH--------------------------------------------------
# define M_PI 3.14159265358979323846
# define M_PI_2 1.5707963268
# define M_PI_3 4.7123889804
# define DR 0.01745329

//-----------------------INCLUDES-------- --------------------------------------
# include <math.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/Xlib.h>
//-----------------------PATH-INCLUDES-----------------------------------------
# include "../lib/minilibx/mlx.h"
# include "../lib/libft/includes/libft.h"

//-----------------------STRUCTS-----------------------------------------------

typedef struct s_player
{
	double		x;
	double		y;
	double		angle;
	double		delta_x;
	double		delta_y;
	float		nextx;
	float		nexty;
	float		speed;
	float		mouse_x;
}	t_player;

typedef struct s_ray
{
	float		angle;
	float		ray_x;
	float		ray_y;
	float		x_offset;
	float		y_offset;
	float		horizontal_x;
	float		horizontal_y;
	float		vertical_x;
	float		vertical_y;
	float		line_height;
	float		line_offset;
	int			ray_width;
	int			ray;
	int			mx;
	int			my;
	int			mp;
	int			deapht_of_field;
	int			h_length;
	int			v_length;
	int			total_length;
	int			win_i;
	int			win_j;
}	t_ray;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			color;
	char		*texture;
}	t_color;

typedef struct s_map
{
	t_color		floor;
	t_color		ceiling;
	char		*temp_map;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*floor_texture;
	char		*ceiling_texture;
	int			*map;
	int			win_w;
	int			win_h;
	int			width;
	int			height;
	int			mapx;
	int			mapy;
	int			maps;
	int			cellsize;
	int			x;
	int			y;
	int			i;
	int			j;
	int			cell;
	int			color;
	int			player;
}	t_map;

typedef struct s_data
{
	float	wall_x;
	float	current_dist;
	float	weight;
	float	current_ceiling_x;
	float	current_ceiling_y;
	float	current_floor_x;
	float	current_floor_y;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	char	*n_addr;
	char	*s_addr;
	char	*w_addr;
	char	*e_addr;
	char	*floor_addr;
	char	*ceiling_addr;
	char	*weapon_addr;
	char	*shot_addr;
	char	*crosshair_addr;
	char	*life_addr;
	char	*door_addr;
	char	*door1_addr;
	void	*door1_texture;
	char	*enem_addr;
	void	*enem_texture;
	void	*door_texture;
	void	*shot_texture;
	void	*life_texture;
	void	*crosshair_texture;
	void	*weapon_texture;
	void	*n_texture;
	void	*s_texture;
	void	*w_texture;
	void	*e_texture;
	void	*f_texture;
	void	*c_texture;
	int		texture_width;
	int		texture_height;
	int		texture_x;
	int		texture_y;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;
}				t_data;

typedef struct s_line
{
	int			dx;
	int			dy;
	int			steps;
	int			k;
	float		xincrement;
	float		yincrement;
	float		x;
	float		y;
	t_ray		*ray;
	int			end_x;
	int			end_y;
}	t_line;

typedef struct s_sprite
{
	float	sprite_x;
	float	sprite_y;
	float	sprite_screen_x;
	float	sprite_screen_y;
	float	distance;
	float	angle_to_sprite;
	float	relative_x;
	float	relative_y;
	int		x;
	int		y;
	int		active;
	int		*texture;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		texture_width;
	int		texture_height;
	int		screen_x;
	int		screen_y;
}	t_sprite;

typedef struct s_game
{
	t_player	player;
	t_map		map;
	t_data		data;
	t_sprite	sprite;
	t_data		texture;
	t_line		line;
	t_ray		rays[90];
	int			focus;
}	t_game;

//-------------------IS-CLOSED-MAP----------------------------------------------
int			check_edges(int idx, t_game *game, int i, int j);
int			validate_map(t_game *game);
int			check_closed_map(t_game *game);

//-----------------------CHECK--------------------------------------------------
int			invalid_texture(t_game *game);
int			textures_and_colors_get(t_game *game);
int			is_north(t_game *game);
int			is_west(t_game *game);
int			have_to_paint(t_map *map);

//-------------------COLOR_TEXT_C+F---------------------------------------------
int			rgb_to_int(t_color color);
int			get_color(char *line);
int			get_rgb(t_color *color, char *line);
int			parse_color(t_game *game, char *line);
int			handle_floor_texture(t_game *game, char *new_line);
int			handle_ceiling_texture(t_game *game, char *new_line);
int			handle_texture_paths(t_game *game, char *new_line);

//-----------------------FILL_MAP-----------------------------------------------
void		setting_map_x_map_y(char *str_map, t_game *game);
int			*str_to_int_array(char *map, int x, int y);
void		handle_char(char c, int *array, int *index, int x);
void		fill_tabs(int *array, int *index);
void		fill_spaces(int *array, int *index, int x);

//-----------------------PARSING-----------------------------------------------
int			parse_file(t_game *game, char *argv);
int			parse_color(t_game *game, char *line);
int			parse_texture_and_colors(t_game *game, char *line);
int			parse_map(t_game *game, char *line);
int			rgb_to_int(t_color color);
int			get_line(t_game *game, char *line, char *temp, int fd);
int			check_line(t_game *game, char *line, char *temp, int fd);
char		*get_path(char *str);

//-----------------------ERROR-------------------------------------------------
int			cub_error(char *str, int error);
int			textures_and_colors_get(t_game *game);
int			mapping(t_game *game);
int			check_doors(t_game *game);

//-----------------------INIT--------------------------------------------------
int			init_game(t_game *game);
void		init_map_size(t_game *game);
void		init_map(t_game *game);
void		init_window(t_game *game);
void		init_parsing_data(t_game *game);
int			init_textures(t_game *game);
void		init_hud(t_game *game);
int			init_floor_ceiling_and_doors(t_game *game);
int			loop(t_game *game);

//--------------------WINDOW--------------------------------------------------
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		set_window(t_game *game);
void		draw_ceiling(t_game *game);
void		draw_floor(t_game *game);
void		draw_walls(t_game *game);
void		draw_window(t_game *game);
int			get_texture_color(int *texture, t_game *game);
void		get_texture_pos(t_game *game);
int			get_texture_color1(int *texture, int tex_x, \
			int tex_y, t_game *game);
int			get_texture_color2(int *texture, int tex_x, \
			int tex_y, t_game *game);
void		select_wall(t_game *game);
void		texture_pos_cf(t_game *game);

//-----------------------PLAYER------------------------------------------------
void		spawn_player(t_game *game);
void		player_movement(int keycode, t_game *game);
void		player_angle(int keycode, t_game *game);
int			key_press(int keycode, t_game *game);
int			is_wall(t_game *game, float x, float y);
int			mouse_move(int x, int y, t_game *game);

//-----------------------MINIMAP----------------------------------------------
void		minimap(t_game *game);
void		draw_ray(t_game *game, int rayIndex, int lenght);
void		draw_player(t_game *game, int width, int height, int color);
void		draw_sprite(t_game *game);

//-----------------------CASTER------------------------------------------------
float		distance(float x1, float y1, float x2, float y2);
void		get_angle(t_game *game);
void		reset_angle(t_game *game);
void		chose_lenght(t_game *game);
void		cast_rays(t_game *game);
void		cast_horizontal(t_game *game);
void		horizontal_direction(t_game *game);
void		reset_horizontal(t_game *game);
void		cast_vertical(t_game *game);
void		vertical_direction(t_game *game);
void		reset_vertical(t_game *game);
void		set_horizontal(t_game *game);
void		set_vertical(t_game *game);

//-----------------------UTILS-------------------------------------------------

void		draw_crosshair(t_game *game);
void		draw_weapon(t_game *game);
void		draw_life(t_game *game);
void		draw_shot(t_game *game);
int			shoot(int button, int x, int y, void *param);
void		check_door(t_game *game);

#endif
