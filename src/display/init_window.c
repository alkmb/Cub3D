/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:13:19 by akambou           #+#    #+#             */
/*   Updated: 2024/06/21 06:54:07 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_doors(t_game *game)
{
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
	game->data.enem_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/door.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	game->data.enem_addr = mlx_get_data_addr(game->data.enem_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
}

void	init_floor_ceiling_and_doors(t_game *game)
{
	if (game->map.floor_texture)
	{
		game->data.f_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
		game->map.floor_texture , &game->data.texture_width, \
		&game->data.texture_height);
		game->data.floor_addr = mlx_get_data_addr(game->data.f_texture, \
		&game->data.bits_per_pixel, &game->data.line_length, \
		&game->data.endian);
	}
	if (game->map.ceiling_texture)
	{
		game->data.c_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
		game->map.ceiling_texture, &game->data.texture_width, \
		&game->data.texture_height);
		game->data.ceiling_addr = mlx_get_data_addr(game->data.c_texture, \
		&game->data.bits_per_pixel, &game->data.line_length, \
		&game->data.endian);
	}
	printf ("ceiling color: %d\n", game->map.ceiling.color);
	printf ("floor color: %d\n", game->map.floor.color);
	init_doors(game);
}

int	init_textures(t_game *game)
{
	init_hud(game);
	if (invalid_texture(game))
		return (FAILURE);
	game->data.n_addr = mlx_get_data_addr(game->data.n_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	game->data.s_addr = mlx_get_data_addr(game->data.s_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);
	game->data.w_addr = mlx_get_data_addr(game->data.w_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);
	game->data.e_addr = mlx_get_data_addr(game->data.e_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	if (!game->data.n_addr || !game->data.s_addr || !game->data.w_addr \
		|| !game->data.e_addr)
		return (FAILURE);
	init_floor_ceiling_and_doors(game);
	return (SUCCESS);
}

void	init_window(t_game *game)
{
	game->map.win_w = 1200;
	game->map.win_h = 800;
	game->data.mlx_ptr = mlx_init();
	init_textures(game);
	game->data.win_ptr = mlx_new_window(game->data.mlx_ptr, \
	game->map.win_w, game->map.win_h, "Game");
	game->data.img = mlx_new_image(game->data.mlx_ptr, \
	game->map.win_w, game->map.win_h);
	game->data.addr = mlx_get_data_addr(game->data.img, \
	&game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);
}

int	init_game(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	game->focus = 1;
	init_window(game);
	spawn_player(game);
	game->player.angle -= (M_PI / 6);
	game->sprite.active = 1;
	game->map.height = game->map.mapy;
	game->map.width = game->map.mapx;
	game->map.win_h = (game->map.mapy * game->map.maps);
	game->map.win_w = (game->map.mapx * game->map.maps);
	return (SUCCESS);
}
