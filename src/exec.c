/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:38:00 by kmb               #+#    #+#             */
/*   Updated: 2024/05/06 01:18:39 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_game(t_game *game)
{
    int x = 0, y = 0;
    game->map.mapX = 25,  game->map.mapY = 14,  game->map.mapS = 64;


    game->mlx.mlx_ptr = mlx_init();
    game->map.width = game->map.mapX * game->map.mapS;
    game->map.height = game->map.mapY * game->map.mapS;
    game->map.cellSize =  game->map.mapS - 1;
    game->mlx.win_ptr2 = mlx_new_window(game->mlx.mlx_ptr, game->map.width, game->map.height, "cub3d1");
    game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, game->map.width, game->map.height, "cub3d");

    game->map.width = 0;
    game->map.height = 0;
    game->map.floor_color.b = 128;
    game->map.floor_color.g = 128;
    game->map.floor_color.r = 128;
    game->map.ceiling_color.b = 0;
    game->map.ceiling_color.g = 0;
    game->map.ceiling_color.r = 0;

    while ( y < game->map.mapY)
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

int loop(t_game *game)
{
    cast_rays(game);
    draw_player(game, 10, 10, 0xFF0000);
    return 0;
}