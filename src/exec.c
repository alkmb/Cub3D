/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobmk <nobmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:38:00 by kmb               #+#    #+#             */
/*   Updated: 2024/06/08 00:11:20 by nobmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_game(t_game *game)
{
    int x = 0, y = 0;
    int *img_width;
    int *img_height;

    img_width = (int *)malloc(sizeof(int));
    img_height = (int *)malloc(sizeof(int));
    *img_width = 32;
    *img_height = 32;
    game->map.mapY -= 1;
    game->map.height = game->map.mapY * game->map.mapS;
    game->map.width = game->map.mapX * game->map.mapS;
    game->map.cell = game->map.map[ game->map.y * \
    game->map.mapX +  game->map.x];
    game->map.cellSize =  game->map.mapS - 1;

    game->data.mlx_ptr = mlx_init(); 


    game->data.win_ptr = mlx_new_window(game->data.mlx_ptr, \
    game->map.width / 2, game->map.height, "Game");

    game->data.img = mlx_new_image(game->data.mlx_ptr, \
    game->map.width / 2, game->map.height);
    
    // game->data.img = mlx_xpm_file_to_image(game->data.mlx_ptr, \
    // "textures/wood.xpm", img_width, img_height);

    game->data.addr = mlx_get_data_addr(game->data.img, \
    &game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);

    game->map.width = 0;
    game->map.height = 0;

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
    draw_player(game, 10, 10, 0xFF0000);
    cast_rays(game);
    return 0;
}
