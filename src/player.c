/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobmk <nobmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 05:42:43 by kmb               #+#    #+#             */
/*   Updated: 2024/05/23 02:34:03 by nobmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Algoritmo de Bresenham para dibujar lineas
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

    k = 0;
    while (k < steps)
    {
        x += xIncrement;
        y += yIncrement;
        mlx_pixel_put(game->mlx.mlx_ptr, \
        game->mlx.win_ptr, round(x), round(y), 0xFFFFFF);
        k++;
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
    cast_rays(game);
    draw_map(game);
}

int is_wall(t_game *game, float x, float y) 
{
    int mapX = (int)(x / game->map.mapS);
    int mapY = (int)(y / game->map.mapS);
    return game->map.map[mapY * game->map.width + mapX] == 1;
}

int key_press(int keycode, t_game *game)
{
    mlx_clear_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
    draw_3D(game);
    float nextX = game->player.x;
    float nextY = game->player.y;

    if (keycode == KEY_W)
    {
        nextX += game->player.delta_x;
        nextY += game->player.delta_y;
    }
    else if (keycode == KEY_S)
    {
        nextX -= game->player.delta_x;
        nextY -= game->player.delta_y;
    }
    else if (keycode == KEY_A)
    {
        nextX -= cos(game->player.angle + (M_PI / 2)) * 5;
        nextY -= sin(game->player.angle + (M_PI / 2)) * 5;
    }
    else if (keycode == KEY_D)
    {
        nextX += cos(game->player.angle + (M_PI / 2)) * 5;
        nextY += sin(game->player.angle + (M_PI / 2)) * 5;
    }
    else if (keycode == KEY_LEFT)
    {
        game->player.angle -= 0.1;
        if (game->player.angle > 0)
            game->player.angle += (2 * M_PI);
        game->player.delta_x = cos(game->player.angle) * 5;
        game->player.delta_y = sin(game->player.angle) * 5;
        cast_rays(game);
    }   
    else if (keycode == KEY_RIGHT)
    {
        game->player.angle += 0.1;
        if (game->player.angle > 0)
            game->player.angle -= (2 * M_PI);
        game->player.delta_x = cos(game->player.angle) * 5;
        game->player.delta_y = sin(game->player.angle) * 5;
        cast_rays(game);
    }
    else if (keycode == KEY_ESC)
        exit(0);

    if (!is_wall(game, nextX, nextY)) {
        game->player.x = nextX;
        game->player.y = nextY;
    }

    return 0;
}