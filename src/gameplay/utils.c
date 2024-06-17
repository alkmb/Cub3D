/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 03:25:53 by akambou           #+#    #+#             */
/*   Updated: 2024/06/17 05:04:10 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	mouse_move(int x, int y, t_game *game)
{
	float	sensitivity;

	sensitivity = 0.0001;
	game->player.angle += (x - game->map.win_w / 2) * sensitivity;
	if (game->player.angle < 0)
		game->player.angle += 2 * M_PI;
	if (game->player.angle > 2 * M_PI)
		game->player.angle -= 2 * M_PI;
	game->player.delta_x = cos(game->player.angle) * 5;
	game->player.delta_y = sin(game->player.angle) * 5;
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	cub_error(char *str, int error)
{
	while (*str)
		write (2, str++, 1);
	return (error);
}

int	close_window(t_game *game)
{
	exit(0);
}

void draw_crosshair(t_game *game)
{
	int x, y;
	x = game->map.win_w / 2 - 16.5;
	y = game->map.win_h / 2 - 16.5;
	game->data.texture_width = 33;
	game->data.texture_height = 33;

	for (int i = 0; i < game->data.texture_width; i++)
	{
		for (int j = 0; j < game->data.texture_height; j++)
		{
			int color = get_texture_color1((int *)game->data.crosshair_addr, i, j, game);
			if (color != 0x0000FF) {
				my_mlx_pixel_put(&game->data, x + i, y + j, color);
			}
		}
	}
	game->data.texture_width = 64;
	game->data.texture_height = 64;
}

void draw_weapon(t_game *game)
{
	int x, y;
	x = game->map.win_w / 2 - 192;
	y = game->map.win_h - 384;
	game->data.texture_width = 384;
	game->data.texture_height = 384;

	for (int i = 0; i < game->data.texture_width; i++)
	{
		for (int j = 0; j < game->data.texture_height; j++)
		{
			int color = get_texture_color1((int *)game->data.weapon_addr, i, j, game);
			if (color != 0x0000FF)
				my_mlx_pixel_put(&game->data, x + i, y + j, color);
		}
	}
	game->data.texture_width = 64;
	game->data.texture_height = 64;
}

void draw_shot(t_game *game)
{
	int x, y;
	x = game->map.win_w / 2 - 192;
	y = game->map.win_h - 384;
	game->data.texture_width = 384;
	game->data.texture_height = 384;

	for (int i = 0; i < game->data.texture_width; i++)
	{
		for (int j = 0; j < game->data.texture_height; j++)
		{
			int color = get_texture_color1((int *)game->data.shot_addr, i, j, game);
			if (color != 0x0000FF)
				my_mlx_pixel_put(&game->data, x + i, y + j, color);
		}
	}
	game->data.texture_width = 64;
	game->data.texture_height = 64;
}

int shoot(int button, int x, int y, void *param)
{
	if (button == 1)
	{
		draw_shot(param);
	}
	return (0);
}
void draw_life(t_game *game)
{
	int x, y;
	x = 0;
	y = game->map.win_h - game->data.texture_height - 20;
	game->data.texture_width = 384;
	game->data.texture_height = 80;

	for (int i = 0; i < game->data.texture_width; i++)
	{
		for (int j = 0; j < game->data.texture_height; j++)
		{
			int color = get_texture_color1((int *)game->data.life_addr, i, j, game);
			if (color != 0x0000FF)
				my_mlx_pixel_put(&game->data, x + i, y + j, color);
		}
	}
	game->data.texture_width = 64;
	game->data.texture_height = 64;
}
int	loop(t_game *game)
{
	cast_rays(game);
	mlx_put_image_to_window(game->data.mlx_ptr, game->data.win_ptr, \
	game->data.img, 0, 0);
	draw_player(game, 8, 8, 0x00FF00);
	draw_crosshair(game);
	draw_weapon(game);
	draw_life(game);
	game->map.y = 0;
	minimap(game);
	game->map.maps *= 8;
	game->map.cellsize *= 8;
	mlx_mouse_move(game->data.mlx_ptr, game->data.win_ptr, \
	(game->map.win_w / 2), game->map.win_h / 2);
	return (0);
}
