/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 03:25:53 by akambou           #+#    #+#             */
/*   Updated: 2024/06/21 05:35:53 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_door(t_game *game)
{
	if (game->map.map[game->rays->mp] == 7)
	{
		get_texture_pos(game);
		if (game->rays->total_length < 50)
			game->data.color = get_texture_color((int *) \
			game->data.door1_addr, game);
		else
			game->data.color = get_texture_color((int *) \
			game->data.door_addr, game);
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	cub_error(char *str, int error)
{
	int	err;

	while (*str)
		err = write (2, str++, 1);
	return (error * err);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->data.mlx_ptr, game->data.win_ptr);
	exit(0);
}

int	loop(t_game *game)
{
	cast_rays(game);
	draw_sprite(game);
	mlx_put_image_to_window(game->data.mlx_ptr, game->data.win_ptr, \
	game->data.img, 0, 0);
	draw_player(game, 8, 8, 0x00FF00);
	draw_crosshair(game);
	draw_weapon(game);
	draw_life(game);
	minimap(game);
	game->map.y = 0;
	game->map.maps *= 8;
	game->map.cellsize *= 8;
	mlx_hook(game->data.win_ptr, 17, 0, close_window, game);
	if (game->focus == 1)
	{
		mlx_mouse_move(game->data.mlx_ptr, game->data.win_ptr, \
		(game->map.win_w / 2), game->map.win_h / 2);
		mlx_mouse_hide(game->data.mlx_ptr, game->data.win_ptr);
	}
	return (0);
}
