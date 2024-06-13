/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 06:27:32 by akambou           #+#    #+#             */
/*   Updated: 2024/06/12 15:22:45 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void    spawn_player(t_game *game)
{
    int x = 0, y = 0;

    while (y < game->map.mapY)
    {
        x = 0;
        while (x < game->map.mapX)
        {
            if (game->map.map[y * game->map.mapX + x] == 3)
            {
                game->player.x = x * game->map.mapS;
                game->player.y = y * game->map.mapS;
                return;
            }
            x++;
        }
        y++;
    }
}

void    player_movement(int keycode, t_game *game)
{
    if (keycode == KEY_W)
    {
        game->player.nextX += game->player.delta_x;
        game->player.nextY += game->player.delta_y;
    }
    else if (keycode == KEY_S)
    {
        game->player.nextX -= game->player.delta_x;
        game->player.nextY -= game->player.delta_y;

    }
    else if (keycode == KEY_A)
    {
        game->player.nextX -= cos(game->player.angle + (M_PI / 2)) * 5;
        game->player.nextY -= sin(game->player.angle + (M_PI / 2)) * 5;
    }
    else if (keycode == KEY_D)
    {
        game->player.nextX += cos(game->player.angle + (M_PI / 2)) * 5;
        game->player.nextY += sin(game->player.angle + (M_PI / 2)) * 5;
    }
}

void   player_angle(int keycode, t_game *game)
{
    if (keycode == KEY_RIGHT)
    {
        game->player.angle += 0.1;
        if (game->player.angle > 0)
            game->player.angle -= (2 * M_PI);
        game->player.delta_x = cos(game->player.angle) * 5;
        game->player.delta_y = sin(game->player.angle) * 5;
    }
    else if (keycode == KEY_LEFT)
    {
        game->player.angle -= 0.1;
        if (game->player.angle > 0)
            game->player.angle -= (2 * M_PI);
        game->player.delta_x = cos(game->player.angle) * 5;
        game->player.delta_y = sin(game->player.angle) * 5;
    }
}

int key_press(int keycode, t_game *game)
{
    draw_window(game);
    game->player.nextX = game->player.x;
    game->player.nextY = game->player.y;

    player_movement(keycode, game);
    player_angle(keycode, game);
    if (keycode == KEY_ESC)
        exit(0);
    if (!is_wall(game, game->player.nextX, game->player.nextY))
    {
        game->player.x = game->player.nextX;
        game->player.y = game->player.nextY;
    }
    return 0;
}

int is_wall(t_game *game, float x, float y) 
{
    int mapX = (int)(x / game->map.mapS);
    int mapY = (int)(y / game->map.mapS);
    return game->map.map[mapY * game->map.width + mapX] == 1;
}