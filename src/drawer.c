/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 05:42:43 by kmb               #+#    #+#             */
/*   Updated: 2024/04/26 06:16:48 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
            mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, game->player.x + j, game->player.y + i, color);
            j++;
        }
        i++;
    }
}

void draw_map(t_game *game)
{
    int x, y, i, j;

    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            for (i = 0; i < SCALE_Y; i++)
            {
                for (j = 0; j < SCALE_X; j++)
                {
                    if (map[y][x] == 1)
                    {
                        // Draw wall
                        mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x * SCALE_X + j, y * SCALE_Y + i, 0x0000FF);
                    }
                    else
                    {
                        // Draw empty space
                        mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x * SCALE_X + j, y * SCALE_Y + i, 0x808080);
                    }

                    // Draw grey line around the space
                    if (i == 0 || i == SCALE_Y - 1 || j == 0 || j == SCALE_X - 1)
                    {
                        mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x * SCALE_X + j, y * SCALE_Y + i, 0xFFFF00);
                    }
                }
            }
        }
    }
}

void draw_player_angle(t_game *game, int length)
{
    int dx, dy, steps, k;
    float xIncrement, yIncrement, x, y;

    int end_x = game->player.x + length * cos(game->player.angle);
    int end_y = game->player.y + length * sin(game->player.angle);

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