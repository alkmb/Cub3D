/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 03:25:53 by akambou           #+#    #+#             */
/*   Updated: 2024/06/15 03:26:37 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	mouse_move(int x, int y, t_game *game)
{
	float	sensitivity;

	sensitivity = 0.00001;
	game->player.angle += (x - 1080 / 2) * sensitivity;
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

int	loop(t_game *game)
{
	cast_rays(game);
	mlx_put_image_to_window(game->data.mlx_ptr, game->data.win_ptr, \
	game->data.img, 0, 0);
	draw_player(game, 5, 5, 0xFF0000);
	game->map.y = 0;
	minimap(game);
	game->map.maps *= 8;
	game->map.cellsize *= 8;
	return (0);
}
