/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:07:46 by kmb               #+#    #+#             */
/*   Updated: 2024/04/26 06:12:10 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 3, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
}; 

void init_game(t_game *game)
{
    int x, y;

    game->mlx.mlx_ptr = mlx_init();
    game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, 1200, 900, "cub3d");

    game->rays->direction = 0;
    game->rays->length = 0;
    game->rays->hit_wall = 0;

    game->map.width = 0;
    game->map.height = 0;
    game->map.floor_color.b = 128;
    game->map.floor_color.g = 128;
    game->map.floor_color.r = 128;
    game->map.ceiling_color.b = 0;
    game->map.ceiling_color.g = 0;
    game->map.ceiling_color.r = 0;

    // Find the player's spawn position in the map
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            if (map[y][x] == 3)
            {
                game->player.x = x * SCALE_X;
                game->player.y = y * SCALE_Y;
                return;
            }
        }
    }
}

int loop(t_game *game)
{
    draw_map(game);
    draw_player(game, 25, 25, 0xFF0000);
    draw_player_angle(game, 300);
    return 0;
}

int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_W)
    {
        game->player.x += game->player.delta_x;
        game->player.y += game->player.delta_y;
    }
    else if (keycode == KEY_S)
    {
        game->player.x -= game->player.delta_x;
        game->player.y -= game->player.delta_y;
    }
    else if (keycode == KEY_A)
    {
        game->player.angle -= 0.1;
        if (game->player.angle > 0)
            game->player.angle += (2 * M_PI);
        game->player.delta_x = cos(game->player.angle) * 5;
        game->player.delta_y = sin(game->player.angle) * 5;
    }   
    else if (keycode == KEY_D)
    {
        game->player.angle += 0.1;
        if (game->player.angle > 0)
            game->player.angle -= (2 * M_PI);
        game->player.delta_x = cos(game->player.angle) * 5;
        game->player.delta_y = sin(game->player.angle) * 5;
    }
    else if (keycode == KEY_ESC)
        exit(0);

    return 0;
}

int main(void)
{
    t_game game;

    init_game(&game);
    mlx_hook(game.mlx.win_ptr, 2, 1L<<0, key_press, &game);
    mlx_loop_hook(game.mlx.mlx_ptr, loop, &game);
    mlx_loop(game.mlx.mlx_ptr);
}