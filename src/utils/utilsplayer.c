/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsplayer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:48:37 by akambou           #+#    #+#             */
/*   Updated: 2024/06/17 21:39:55 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	shoot(int button, int x, int y, void *param)
{
	int	i;

	i = 0;
	if (button == 1)
	{
		while (i < 20)
		{
			draw_shot(param);
			i++;
		}

	}
	return (0);
}

int	is_wall(t_game *game, float x, float y)
{
	int	mapx;
	int	mapy;

	mapx = (int)(x / game->map.maps);
	mapy = (int)(y / game->map.maps);
	return (game->map.map[mapy * game->map.width + mapx] == 1);
}

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

void	draw_player(t_game *game, int width, int height, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			mlx_pixel_put(game->data.mlx_ptr, game->data.win_ptr, \
			(game->player.x / 8) + j, (game->player.y / 8) + i, color);
			j++;
		}
		i++;
	}
	game->map.maps /= 8;
	game->map.cellsize /= 8;
}
