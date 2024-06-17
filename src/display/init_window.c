/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:13:19 by akambou           #+#    #+#             */
/*   Updated: 2024/06/17 14:00:09 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_map(t_game *game)
{
	game->map.height = (game->map.mapy * game->map.maps);
	game->map.width = (game->map.mapx * game->map.maps);
	game->map.cell = game->map.map[game->map.y * \
	game->map.mapx + game->map.x];
	game->map.cellsize = game->map.maps - 1;
}

void	init_floor_ceiling_and_doors(t_game *game)
{
	game->data.f_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/floor1.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	game->data.floor_addr = mlx_get_data_addr(game->data.f_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	game->data.c_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/metal1.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	game->data.ceiling_addr = mlx_get_data_addr(game->data.c_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	game->data.door_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/door.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	game->data.door_addr = mlx_get_data_addr(game->data.door_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	game->data.door1_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/door_o.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	game->data.door1_addr = mlx_get_data_addr(game->data.door1_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
}

void	init_textures(t_game *game)
{
	init_hud(game);
	game->data.n_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	game->map.north_texture, &game->data.texture_width, \
	&game->data.texture_height);
	game->data.n_addr = mlx_get_data_addr(game->data.n_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	game->data.s_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	game->map.south_texture, &game->data.texture_width, \
	&game->data.texture_height);
	game->data.s_addr = mlx_get_data_addr(game->data.s_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);
	game->data.w_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	game->map.west_texture, &game->data.texture_width, \
	&game->data.texture_height);
	game->data.w_addr = mlx_get_data_addr(game->data.w_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);
	game->data.e_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	game->map.east_texture, &game->data.texture_width, \
	&game->data.texture_height);
	game->data.e_addr = mlx_get_data_addr(game->data.e_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	init_floor_ceiling_and_doors(game);
}

void	init_window(t_game *game)
{
	game->data.mlx_ptr = mlx_init();
	init_textures(game);
	game->data.win_ptr = mlx_new_window(game->data.mlx_ptr, \
	1200, 800, "Game");
	game->data.img = mlx_new_image(game->data.mlx_ptr, \
	1200, 800);
	game->data.addr = mlx_get_data_addr(game->data.img, \
	&game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);
}

void	init_game(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	init_map(game);
	init_window(game);
	spawn_player(game);
	game->player.angle -= (M_PI / 6);
	game->map.height = game->map.mapy;
	game->map.width = game->map.mapx;
	game->map.win_h = (game->map.mapy * game->map.maps);
	game->map.win_w = (game->map.mapx * game->map.maps);
}
