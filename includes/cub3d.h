/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:06:23 by kmb               #+#    #+#             */
/*   Updated: 2024/04/26 06:08:27 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//-----------------------DEFINES------------------------------------------------
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 900
# define SCALE_X WINDOW_WIDTH / MAP_WIDTH
# define SCALE_Y WINDOW_HEIGHT / MAP_HEIGHT
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define MAP_WIDTH 10
# define MAP_HEIGHT 10
# define M_PI 3.14159265358979323846

//-----------------------INCLUDES----------------------------------------------
# include <math.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
//-----------------------PATH-INCLUDES-----------------------------------------
# include "../minilibx/mlx.h"
# include "../libft/includes/libft.h"

//-----------------------STRUCTS-----------------------------------------------

typedef struct s_mlx
{
    void    *mlx_ptr;
    void    *win_ptr;
}   t_mlx;

typedef struct s_player
{
    double x;
    double y;
    double delta_x;
    double delta_y;
    double angle;
    double rotation_angle;
}   t_player;

typedef struct s_ray
{
    double direction;
    double length;
    int hit_wall;
}   t_ray;

typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

typedef struct s_map
{
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    t_color floor_color;
    t_color ceiling_color;
    char **data;
    int width;
    int height;
}   t_map;

typedef struct s_game
{
    t_mlx mlx;
    t_player player;
    t_map map;
    t_ray rays[WINDOW_WIDTH];
}   t_game;

extern int map[MAP_HEIGHT][MAP_WIDTH];

//-----------------------PROTOTYPES--------------------------------------------
//-----------------------INIT--------------------------------------------------
void    init_game(t_game *game);
//-----------------------DRAW--------------------------------------------------
void    draw_map(t_game *game);
void    draw_player(t_game *game, int width, int height, int color);
void    draw_player_angle(t_game *game, int length);

#endif