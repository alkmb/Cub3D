/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:06:23 by kmb               #+#    #+#             */
/*   Updated: 2024/04/25 04:50:11 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
    double direction;
    double speed;
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
    t_ray rays;
}   t_game;

//-----------------------PROTOTYPES--------------------------------------------
//-----------------------INIT--------------------------------------------------
void    init_game(t_game *game);

#endif