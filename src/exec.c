/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:38:00 by kmb               #+#    #+#             */
/*   Updated: 2024/06/12 15:51:00 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void init_map(t_game *game)
{
    game->map.mapY -= 1;
    game->map.height = game->map.mapY * game->map.mapS;
    game->map.width = game->map.mapX * game->map.mapS;
    game->map.cell = game->map.map[ game->map.y * \
    game->map.mapX +  game->map.x];
    game->map.cellSize =  game->map.mapS - 1;
}

void init_textures(t_game *game)
 {
    game->data.n_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
    "textures/wood.xpm", &game->data.texture_width, &game->data.texture_height);
    game->data.n_addr = mlx_get_data_addr(game->data.n_texture, \
    &game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);

    game->data.s_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
    "textures/brick.xpm", &game->data.texture_width, &game->data.texture_height);
    game->data.s_addr = mlx_get_data_addr(game->data.s_texture, \
    &game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);

    game->data.w_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
    "textures/hitler.xpm", &game->data.texture_width, &game->data.texture_height);
    game->data.w_addr = mlx_get_data_addr(game->data.w_texture, \
    &game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);

    game->data.e_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \  
    "textures/eagle.xpm", &game->data.texture_width, &game->data.texture_height);
    game->data.e_addr = mlx_get_data_addr(game->data.e_texture, \
    &game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);
 }

void    init_window(t_game* game)
{
    game->data.texture_width = 64;
    game->data.texture_height = 64;
    
    game->data.mlx_ptr = mlx_init(); 
    game->data.win_ptr = mlx_new_window(game->data.mlx_ptr, \
    game->map.width / 2, game->map.height, "Game");
    init_textures(game);
    game->data.img = mlx_new_image(game->data.mlx_ptr, \
    game->map.width, game->map.height);
    game->data.addr = mlx_get_data_addr(game->data.img, \
    &game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);
}

void init_game(t_game *game)
{
    int x = 0, y = 0;

    init_map(game);
    init_window(game);
    spawn_player(game);
    game->map.height = game->map.mapY;
    game->map.width = game->map.mapX;
}

void    set_window(t_game *game)
{
    game->map.win_h = game->map.mapY * game->map.mapS;
    game->map.win_w = game->map.mapX * game->map.mapS;
    game->rays->ray_width = game->map.win_w / 120;
    game->rays->line_height = (game->map.mapS * \
    game->map.win_h) / game->rays->total_length;

    if (game->rays->line_height > game->map.win_h)
        game->rays->line_height = game->map.win_h;
    game->rays->line_offset = game->map.win_h / 2 - \
    game->rays->line_height / 2;
}

int loop(t_game *game)
{
    cast_rays(game);
    return 0;
}