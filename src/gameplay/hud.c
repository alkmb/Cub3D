/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:43:27 by akambou           #+#    #+#             */
/*   Updated: 2024/06/17 13:51:28 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_hud(t_game *game)
{
	game->data.weapon_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/HUD/pistol.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	game->data.weapon_addr = mlx_get_data_addr(game->data.weapon_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	game->data.crosshair_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/HUD/aim.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	game->data.crosshair_addr = mlx_get_data_addr(game->data.crosshair_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	game->data.life_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/HUD/lifebar.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	game->data.life_addr = mlx_get_data_addr(game->data.life_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	game->data.shot_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/HUD/shot.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	game->data.shot_addr = mlx_get_data_addr(game->data.shot_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
}

void	draw_crosshair(t_game *game)
{
	int	x;
	int	i;
	int	y;
	int	j;

	x = game->map.win_w / 2 - 16.5;
	y = game->map.win_h / 2 - 16.5;
	game->data.texture_width = 33;
	game->data.texture_height = 33;
	i = 0;
	while (i < game->data.texture_width)
	{
		j = 0;
		while (j < game->data.texture_height)
		{
			game->data.color = get_texture_color1((int *) \
			game->data.crosshair_addr, i, j, game);
			if (game->data.color != 0x0000FF)
				my_mlx_pixel_put(&game->data, x + i, y + j, game->data.color);
			j++;
		}
		i++;
	}
	game->data.texture_width = 64;
	game->data.texture_height = 64;
}

void	draw_weapon(t_game *game)
{
	int	x;
	int	i;
	int	y;
	int	j;

	x = game->map.win_w / 2 - 192;
	y = game->map.win_h - 384;
	game->data.texture_width = 384;
	game->data.texture_height = 384;
	i = 0;
	while (i < game->data.texture_width)
	{
		j = 0;
		while (j < game->data.texture_height)
		{
			game->data.color = get_texture_color1((int *) \
			game->data.weapon_addr, i, j, game);
			if (game->data.color != 0x0000FF)
				my_mlx_pixel_put(&game->data, x + i, y + j, game->data.color);
			j++;
		}
		i++;
	}
	game->data.texture_width = 64;
	game->data.texture_height = 64;
}

void	draw_shot(t_game *game)
{
	int	x;
	int	i;
	int	y;
	int	j;

	x = game->map.win_w / 2 - 192;
	y = game->map.win_h - 384;
	game->data.texture_width = 384;
	game->data.texture_height = 384;
	i = 0;
	while (i < game->data.texture_width)
	{
		j = 0;
		while (j < game->data.texture_height)
		{
			game->data.color = get_texture_color1((int *) \
			game->data.shot_addr, i, j, game);
			if (game->data.color != 0x0000FF)
				my_mlx_pixel_put(&game->data, x + i, y + j, game->data.color);
			j++;
		}
		i++;
	}
	game->data.texture_width = 64;
	game->data.texture_height = 64;
}

void	draw_life(t_game *game)
{
	int	x;
	int	i;
	int	y;
	int	j;

	x = 0;
	y = game->map.win_h - game->data.texture_height - 20;
	game->data.texture_width = 384;
	game->data.texture_height = 80;
	i = 0;
	while (i < game->data.texture_width)
	{
		j = 0;
		while (j < game->data.texture_height)
		{
			game->data.color = get_texture_color1((int *) \
			game->data.life_addr, i, j, game);
			if (game->data.color != 0x0000FF)
				my_mlx_pixel_put(&game->data, x + i, y + j, game->data.color);
			j++;
		}
		i++;
	}
	game->data.texture_width = 64;
	game->data.texture_height = 64;
}
