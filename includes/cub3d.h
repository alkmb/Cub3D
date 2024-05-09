/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:06:23 by kmb               #+#    #+#             */
/*   Updated: 2024/05/06 01:54:04 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
//-----------------------DEFINES------------------------------------------------
//-----------------------KEYS--------------------------------------------------
# define KEY_W 119
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

typedef struct s_mlx
{
    void    *mlx_ptr, *win_ptr, *win_ptr2;
}   t_mlx;

typedef struct s_player
{
    double x, y, angle, delta_x, delta_y;
}   t_player;

typedef struct s_ray
{
    float angle, ray_x, ray_y, x_offset, y_offset, \
    horizontal_x, horizontal_y, vertical_x, vertical_y, \
    line_height, line_offset;
    int ray, mx, my, mp, deapht_of_field, h_length, v_length, total_length;
}   t_ray;

typedef struct s_color
{
    int r, g, b;
}   t_color;

typedef struct s_map
{
    char *north_texture, *south_texture, *west_texture, *east_texture;
    t_color floor_color;
    t_color ceiling_color;
    int *map;
    int win_w, win_h ,width, height, mapX, mapY, mapS, cellSize, x, y, i, j, cell, color;
}   t_map;

typedef struct s_game
{
    t_mlx mlx;
    t_player player;
    t_map map;
    t_ray rays[60];
}   t_game;

extern int map[];

//-----------------------PROTOTYPES--------------------------------------------
//-----------------------INIT--------------------------------------------------
void    init_game(t_game *game);
//-----------------------LOOP--------------------------------------------------
int     loop(t_game *game);
//--------------------WINDOW--------------------------------------------------
void    draw_map(t_game *game);
//-----------------------PLAYER------------------------------------------------
int     key_press(int keycode, t_game *game);
void    draw_player(t_game *game, int width, int height, int color);
void    draw_player_angle(t_game *game, int rayIndex, int lenght);
//-----------------------CASTER------------------------------------------------
void    cast_rays(t_game *game);
void    draw_3D(t_game *game);
//-----------------------HORIZONTAL--------------------------------------------
void    cast_horizontal(t_game *game);
void    horizontal_direction(t_game *game);
void    reset_horizontal(t_game *game);
//-----------------------VERTICAL----------------------------------------------
void    cast_vertical(t_game *game);
void    vertical_direction(t_game *game);
void    reset_vertical(t_game *game);
//-----------------------UTILS-------------------------------------------------
float       distance(float x1, float y1, float x2, float y2);
void        chose_length(t_game *game);
void        reset_angle(t_game *game);
void        get_angle(t_game *game);
#endif
