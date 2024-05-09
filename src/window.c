/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 05:49:01 by kmb               #+#    #+#             */
/*   Updated: 2024/05/06 02:20:17 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_player_angle(t_game *game, int rayIndex, int length)
{
    int dx, dy, steps, k;
    float xIncrement, yIncrement, x, y;

    if (rayIndex < 0 || rayIndex >= game->map.width) return;

    t_ray *ray = &game->rays[rayIndex];

    int end_x = game->player.x + length * cos(ray->angle);
    int end_y = game->player.y + length * sin(ray->angle);

    dx = end_x - game->player.x;
    dy = end_y - game->player.y;

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    xIncrement = dx / (float) steps;
    yIncrement = dy / (float) steps;

    x = game->player.x;
    y = game->player.y;

    for (k = 0; k < steps; k++)
    {
        x += xIncrement;
        y += yIncrement;
        mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, round(x), round(y), 0xFFFFFF);
    }
}

void    draw_3D(t_game *game)
{
    game->map.win_h = game->map.mapY * game->map.mapS;
    game->map.win_w = game->map.mapX * game->map.mapS;
    int ray_width = game->map.win_w / 90;
    game->rays->line_height = (game->map.mapS * game->map.win_h) / game->rays->total_length;
    if (game->rays->line_height > game->map.win_h)
        game->rays->line_height = game->map.win_h;
    game->rays->line_offset = game->map.win_h / 2 - game->rays->line_height / 2;
    for (int i = 0; i < game->rays->line_height; i++) {
        for (int j = 0; j < ray_width; j++) {
            int x_position = game->rays->ray * ray_width + j;
            if (x_position < game->map.win_w) {
                mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr2, x_position, game->rays->line_offset + i, 0xFF0000);
            }
        }
    }   
}

void draw_map(t_game *game)
{
    game->map.x = 0,  game->map.y = 0,  game->map.i = 0,  game->map.j = 0;
    game->map.cellSize =  game->map.mapS - 1;

    game->map.height = game->map.mapY;
    game->map.width = game->map.mapX;
    while ( game->map.y <  game->map.mapY)
    {
        game->map.x = 0;
        while ( game->map.x <  game->map.mapX)
        {
            game->map.cell = game->map.map[ game->map.y *  game->map.mapX +  game->map.x];
             game->map.color =  game->map.cell == 1 ? 0x0000FF : 0x808080;
             game->map.i = 0;
            while ( game->map.i <  game->map.cellSize)
            {
                 game->map.j = 0;
                while ( game->map.j <  game->map.cellSize)
                {
                    mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr,\
                      game->map.x *  game->map.mapS +  game->map.j,  game->map.y *  game->map.mapS +  game->map.i,  game->map.color);
                     game->map.j++;
                }
                 game->map.i++;
            }
            game->map.j = 0;
            while (game->map.j < game->map.mapS) {
                mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, \
                game->map.x * game->map.mapS + game->map.j, game->map.y * game->map.mapS + game->map.cellSize, 0xFFFFFF);
                game->map.j++;
            }

            game->map.i = 0;
            while (game->map.i < game->map.mapS) {
                mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, game->map.x \
                * game->map.mapS + game->map.cellSize, game->map.y * game->map.mapS + game->map.i, 0xFFFFFF);
                game->map.i++;
            }
             game->map.x++;
        }
         game->map.y++;
    }

}

void draw_player(t_game *game, int width, int height, int color)
{
    int i;
    int j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, \
             game->player.x + j, game->player.y + i, color);
            j++;
        }
        i++;
    }
    draw_map(game);
}