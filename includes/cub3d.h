/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:06:23 by kmb               #+#    #+#             */
/*   Updated: 2024/06/13 02:44:19 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
//-----------------------DEFINES------------------------------------------------
# define SUCCESS 0
# define FAILURE 1
# define TRUE 1
#define FALSE 0
# define FLOOR_COLOR 0xFF0000
# define CEILING_COLOR 0x00FF00
//-----------------------KEYS--------------------------------------------------
# define KEY_W 119
# define EVENT_CLOSE_BTN 17
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
//-----------------------MATH--------------------------------------------------
# define M_PI 3.14159265358979323846
# define M_PI_2 M_PI / 2
# define M_PI_3 3 * M_PI / 2
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
//-----------------------PATH-INCLUDES-----------------------------------------
# include "../lib/minilibx/mlx.h"
# include "../lib/libft/includes/libft.h"

//-----------------------STRUCTS-----------------------------------------------

typedef struct s_player
{
    double	x;
	double	y;
	double	angle;
	double	delta_x;
	double	delta_y;
	float	nextX;
	float	nextY;
}   t_player;

typedef struct s_ray
{
    float	angle;
	float	ray_x;
	float	ray_y;
	float	x_offset;
	float	y_offset;
    float	horizontal_x; 
	float	horizontal_y; 
	float	vertical_x;
	float	vertical_y;
    float	line_height;
	float	line_offset;
    int 	ray_width;
	int		ray;
	int		mx;
	int		my;
	int		mp;
	int		deapht_of_field;
	int		h_length;
	int		v_length;
	int		total_length;
	int		win_i;
	int		 win_j;
}   t_ray;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		color;
}   t_color;

typedef struct s_map
{
	t_color	floor;
	t_color	ceiling;
	char	*temp_map;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		*map;
	int		win_w;
	int		win_h;
	int		width;
	int		height;
	int		mapX;
	int		mapY;
	int		mapS;
	int		cellSize;
	int		x;
	int		y;
	int		i;
	int		j;
	int		cell;
	int		color;
}	t_map;

typedef struct	s_data
{
	float   wall_x;
	void    *mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	char	*n_addr;
	char	*s_addr;
	char	*w_addr;
	char	*e_addr;
	void	*n_texture;
	void	*s_texture;
	void	*w_texture;
	void	*e_texture;
	int    	texture_width;
	int    	texture_height;
	int	 	texture_x;
	int	 	texture_y;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;
}				t_data;

typedef struct s_game
{
    t_player player;
    t_map map;
	t_data data;
	t_data texture;
    t_ray rays[60];
}   t_game;

extern int map[];


//-----------------------PARSING-----------------------------------------------
int			parse_file(t_game *game, char *argv);
int			parse_color(t_game *game, char *line);
void		parse_texture_and_colors(t_game *game, char *line);
int			parse_map(t_game *game, char *line);
int			rgb_to_int(t_color color);

//-----------------------ERROR-------------------------------------------------
int			cub_error(char *str, int error);

//-----------------------CHECK--------------------------------------------------
int			textures_and_colors_get(t_game *game);
int			mapping(t_game *game);

//-----------------------INIT--------------------------------------------------
void    	init_game(t_game *game);
void    	init_map(t_game *game);
void    	init_window(t_game *game);
void    	init_parsing_data(t_game *game);
int     	loop(t_game *game);

//--------------------WINDOW--------------------------------------------------
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    	set_window(t_game *game);
void    	draw_cealing(t_game *game);
void    	draw_floor(t_game *game);
void    	draw_walls(t_game *game);
void    	draw_window(t_game *game);

//-----------------------PLAYER------------------------------------------------
void    	spawn_player(t_game *game);
void    	player_movement(int keycode, t_game *game);
void		player_angle(int keycode, t_game *game);
int     	key_press(int keycode, t_game *game);
int	        is_wall(t_game *game, float x, float y);

//-----------------------MINIMAP----------------------------------------------
void    	minimap(t_game *game);
void    	draw_ray(t_game *game, int rayIndex, int lenght);
void    	draw_player(t_game *game, int width, int height, int color);

//-----------------------CASTER------------------------------------------------
float       distance(float x1, float y1, float x2, float y2);
void        get_angle(t_game *game);
void        reset_angle(t_game *game);
void    	chose_lenght(t_game *game);
void    	cast_rays(t_game *game);
void    	cast_horizontal(t_game *game);
void   		horizontal_direction(t_game *game);
void    	reset_horizontal(t_game *game);
void    	cast_vertical(t_game *game);
void    	vertical_direction(t_game *game);
void	    reset_vertical(t_game *game);

//-----------------------UTILS-------------------------------------------------

#endif
