/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobmk <nobmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 824/05/06 01:39:32 by kmb               #+#    #+#             */
/*   Updated: 824/05/23 01:02:32 by nobmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    cast_horizontal(t_game *game)
{
    while (game->rays->deapht_of_field < 8)
    {
        game->rays->mx = (int)game->rays->ray_x >> 6;
        game->rays->my = (int)game->rays->ray_y >> 6;
        if (game->rays->mx >= 0 && game->rays->mx < game->map.width 
        && game->rays->my >= 0 && game->rays->my < game->map.height) {
            game->rays->mp = game->rays->my * game->map.width + game->rays->mx;
        }
        if (game->rays->mp > 0 && game->rays->mp < game->map.width * \
        game->map.height && game->map.map[game->rays->mp] == 1)
        {
            game->rays->horizontal_x = game->rays->ray_x;
            game->rays->horizontal_y = game->rays->ray_y;
            game->rays->h_length = distance(game->player.x, \
            game->player.y, game->rays->horizontal_x, game->rays->horizontal_y);
            game->rays->deapht_of_field = 8;
        }
        else
        {
            game->rays->ray_x += game->rays->x_offset;
            game->rays->ray_y += game->rays->y_offset;
            game->rays->h_length = distance(game->player.x, \
            game->player.y, game->rays->ray_x, game->rays->ray_y);
            game->rays->deapht_of_field++;
        }
    }
}

void    horizontal_direction(t_game *game)
{
    float aTan = -1 / tan(game->rays->angle);
    if (game->rays->angle > M_PI)
    {
        game->rays->ray_y = (((int)game->player.y >> 6) << 6) - 0.0001;
        game->rays->ray_x = (game->player.y - game->rays->ray_y) * \
        aTan + game->player.x;
        game->rays->y_offset = -64;
        game->rays->x_offset = -game->rays->y_offset * aTan;
    }
    if (game->rays->angle < M_PI)
    {
        game->rays->ray_y = (((int)game->player.y >> 6) << 6) + 64;
        game->rays->ray_x = (game->player.y - game->rays->ray_y) * \
        aTan + game->player.x;
        game->rays->y_offset = 64;
        game->rays->x_offset = -game->rays->y_offset * aTan;
    }
    if (game->rays->angle == 0 || game->rays->angle == M_PI)
    {
        game->rays->ray_x = game->player.x;
        game->rays->ray_y = game->player.y;
        game->rays->deapht_of_field = 8;
    }
}


void    reset_horizontal(t_game *game)
{
        game->rays->h_length = 100000000;
        game->rays->horizontal_x = game->player.x;
        game->rays->horizontal_y = game->player.y;
        game->rays->deapht_of_field = 0;
}