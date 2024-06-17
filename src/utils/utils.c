/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 03:25:53 by akambou           #+#    #+#             */
/*   Updated: 2024/06/17 14:09:03 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_door(t_game *game)
{
	if (game->map.map[game->rays->mp] == 7 && game->rays->win_i \
	< game->map.win_h)
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
	while (*str)
		write (2, str++, 1);
	return (error);
}

int	close_window(t_game *game)
{
	exit(0);
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
